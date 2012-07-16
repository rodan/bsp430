#include <bsp430/platform.h>
#include <bsp430/clock.h>
#include <bsp430/periph/euscia_.h>
#include "task.h"

/* !BSP430! periph=euscia */
/* !BSP430! instance=EUSCI_A0,EUSCI_A1,EUSCI_A2 */

#define COM_PORT_ACTIVE  0x01

/* Work around missing vector definitions for EUSCI devices */
#define EUSCI_A0_VECTOR USCI_A0_VECTOR 
#define EUSCI_A1_VECTOR USCI_A1_VECTOR 
#define EUSCI_A2_VECTOR USCI_A2_VECTOR 
#define EUSCI_B0_VECTOR USCI_B0_VECTOR 

/** Convert from a raw peripheral handle to the corresponding USCI
 * device handle. */
static xBSP430eusciaHandle periphToDevice (xBSP430periphHandle periph);

xBSP430eusciaHandle
xBSP430eusciaOpenUART (xBSP430periphHandle periph,
					   unsigned int control_word,
					   unsigned long baud,
					   xQueueHandle rx_queue,
					   xQueueHandle tx_queue)
{
	unsigned short aclk_Hz;
	unsigned long brclk_Hz;
	xBSP430eusciaHandle device = periphToDevice(periph);
	unsigned long n;
	uint16_t br;
	uint16_t os16 = 0;
	uint16_t brf = 0;
	uint16_t brs;

	configASSERT(NULL != device);

	/* Reject invalid baud rates */
	if ((0 == baud) || (1000000UL < baud)) {
		return NULL;
	}

	/* Reject if the pins can't be configured */
	if (0 != iBSP430platformConfigurePeripheralPins((xBSP430periphHandle)(device->euscia), 1)) {
		return NULL;
	}

	device->rx_queue = rx_queue;
	device->tx_queue = tx_queue;

	/* Assume ACLK <= 20 kHz is VLOCLK and cannot be trusted.  Prefer
	 * 32 kiHz ACLK for rates that are low enough.  Use SMCLK for
	 * anything larger.  */
	aclk_Hz = usBSP430clockACLK_Hz();
	if ((aclk_Hz > 20000) && (aclk_Hz >= (3 * baud))) {
		device->euscia->ctlw0 = UCSWRST | UCSSEL__ACLK;
		brclk_Hz = portACLK_FREQUENCY_HZ;
	} else {
		device->euscia->ctlw0 = UCSWRST | UCSSEL__SMCLK;
		brclk_Hz = ulBSP430clockSMCLK_Hz();
	}
#define BR_FRACTION_SHIFT 6
	/* The value for BRS is supposed to be a table lookup based on the
	 * fractional part of f_brclk / baud.  Rather than replicate the
	 * table, we simply preserve BR_FRACTION_SHIFT bits of the
	 * fraction, then use that as the upper bits of the value of
	 * BRS.  Seems to work, at least for 9600 baud. */
	n = (brclk_Hz << BR_FRACTION_SHIFT) / baud;
	brs = n & ((1 << BR_FRACTION_SHIFT) - 1);
	n >>= BR_FRACTION_SHIFT;
	brs <<= 8 - BR_FRACTION_SHIFT;
#undef BR_FRACTION_SHIFT
	br = n;
	if (16 <= br) {
		br = br / 16;
		os16 = UCOS16;
		brf = n - 16 * br;
	}
	device->euscia->brw = br;
	device->euscia->mctlw = (brf * UCBRF0) | (brs * UCBRS0) | os16;

	/* Mark the device active */
	device->num_rx = device->num_tx = 0;
	device->flags |= COM_PORT_ACTIVE;

	/* Release the USCI and enable the interrupts.  Interrupts are
	 * disabled and cleared when UCSWRST is set. */
	device->euscia->ctlw0 &= ~UCSWRST;
	if (0 != device->rx_queue) {
		device->euscia->ie |= UCRXIE;
	}

	return device;
}

int
iBSP430eusciaClose (xBSP430eusciaHandle device)
{
	device->euscia->ctlw0 = UCSWRST;
	iBSP430platformConfigurePeripheralPins ((xBSP430periphHandle)(device->euscia), 0);
	device->tx_queue = 0;
	device->rx_queue = 0;
	device->flags = 0;
	return 0;
}

/* If there's data in the transmit queue, and the transmit interrupt
 * is not enabled, then enable the interrupt.  Do NOT muck with TXIFG,
 * since it may be that the ISR just completed draining the queue but
 * the data has not been transmitted, in which case setting TXIFG
 * would cause the in-progress transmission to be corrupted.
 *
 * For this to work, of course, nobody else should ever muck with the
 * TXIFG bit.  Normal management of this bit via UCSWRST is
 * correct. */
#define USCI_WAKEUP_TRANSMIT_FROM_ISR(device) do {			\
		if ((! xQueueIsQueueEmptyFromISR(device->tx_queue)) \
			&& (! (device->euscia->ie & UCTXIE))) {			\
			device->euscia->ie |= UCTXIE;						\
		}													\
	} while (0)

void
vBSP430eusciaWakeupTransmit (xBSP430eusciaHandle device)
{
	BSP430_ENTER_CRITICAL();
	USCI_WAKEUP_TRANSMIT_FROM_ISR(device);
	BSP430_EXIT_CRITICAL();
}

#define RAW_TRANSMIT(_periph, _c) do {			\
		while (! (_periph->ifg & UCTXIFG)) {	\
			;									\
		}										\
		_periph->txbuf = _c;					\
	} while (0)

int
iBSP430eusciaPutc (int c, xBSP430eusciaHandle device)
{
	const portTickType MAX_DELAY = portMAX_DELAY; // 2000;
	portTickType delay = 0;
	int passp;

	if (device->tx_queue) {
		do {
			passp = xQueueSendToBack(device->tx_queue, &c, delay);
			vBSP430eusciaWakeupTransmit(device);
			if (! passp) {
				delay = MAX_DELAY;
			}
		} while (! passp);
	} else {
		RAW_TRANSMIT(device->euscia, c);
	}
	return c;
}

int
iBSP430eusciaPuts (const char* str, xBSP430eusciaHandle device)
{
	const portTickType MAX_DELAY = portMAX_DELAY; // 2000;
	portTickType delay = 0;
	const char * in_string = str;
	
	if (device->tx_queue) {
		while (*str) {
			if (xQueueSendToBack(device->tx_queue, str, delay)) {
				++str;
				if (delay) {
					vBSP430eusciaWakeupTransmit(device);
					delay = 0;
				}
			} else {
				vBSP430eusciaWakeupTransmit(device);
				delay = MAX_DELAY;
			}
		}
		vBSP430eusciaWakeupTransmit(device);
	} else {
		while (*str) {
			RAW_TRANSMIT(device->euscia, *str);
			++str;
		}
	}
	return str - in_string;
}

/* Since the interrupt code is the same for all peripherals, on MCUs
 * with multiple USCI devices it is more space efficient to share it.
 * This does add an extra call/return for some minor cost in stack
 * space.
 *
 * Making the implementation function __c16__ ensures it's legitimate
 * to use portYIELD_FROM_ISR().
 *
 * Adding __always_inline__ supports maintainability by having a
 * single implementation but speed by forcing the implementation into
 * each handler.  It's a lot cleaner than defining the body as a
 * macro.  GCC will normally inline the code if there's only one call
 * point; there should be a configPORT_foo option to do so in other
 * cases. */

static void
#if __MSP430X__
__attribute__ ( ( __c16__ ) )
#endif /* CPUX */
/* __attribute__((__always_inline__)) */
euscia_irq (xBSP430eusciaHandle device)
{
	portBASE_TYPE yield = pdFALSE;
	portBASE_TYPE rv = pdFALSE;
	uint8_t c;

	switch (device->euscia->iv) {
	default:
	case USCI_NONE:
		break;
	case USCI_UART_UCTXIFG: /* == USCI_SPI_UCTXIFG */
		rv = xQueueReceiveFromISR(device->tx_queue, &c, &yield);
		if (xQueueIsQueueEmptyFromISR(device->tx_queue)) {
			signed portBASE_TYPE sema_yield = pdFALSE;
			device->euscia->ie &= ~UCTXIE;
			yield |= sema_yield;
		}
		if (rv) {
			++device->num_tx;
			device->euscia->txbuf = c;
		}
		break;
	case USCI_UART_UCRXIFG: /* == USCI_SPI_UCRXIFG */
		c = device->euscia->rxbuf;
		++device->num_rx;
		rv = xQueueSendToBackFromISR(device->rx_queue, &c, &yield);
		break;
	}
	portYIELD_FROM_ISR(yield);
}

/* !BSP430! insert=hpl_ba_defn */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [hpl_ba_defn] */
#if configBSP430_PERIPH_EUSCI_A0 - 0
static struct xBSP430eusciaState state_EUSCI_A0_ = {
	.euscia = (xBSP430periphEUSCIA *)__MSP430_BASEADDRESS_EUSCI_A0__
};

xBSP430eusciaHandle const xBSP430euscia_EUSCI_A0 = &state_EUSCI_A0_;

#if configBSP430_PERIPH_EUSCI_A0_ISR - 0
#if ! (configBSP430_SHARE_EUSCIA_ISR - 0)
#error Shared periphal HAL ISR disabled
#endif /* configBSP430_SHARE_EUSCIA_ISR */
static void
__attribute__((__interrupt__(EUSCI_A0_VECTOR)))
irq_EUSCI_A0 (void)
{
	euscia_irq(xBSP430euscia_EUSCI_A0);
}
#endif /* configBSP430_EUSCIA_EUSCI_A0_ISR */

#endif /* configBSP430_PERIPH_EUSCI_A0 */

#if configBSP430_PERIPH_EUSCI_A1 - 0
static struct xBSP430eusciaState state_EUSCI_A1_ = {
	.euscia = (xBSP430periphEUSCIA *)__MSP430_BASEADDRESS_EUSCI_A1__
};

xBSP430eusciaHandle const xBSP430euscia_EUSCI_A1 = &state_EUSCI_A1_;

#if configBSP430_PERIPH_EUSCI_A1_ISR - 0
#if ! (configBSP430_SHARE_EUSCIA_ISR - 0)
#error Shared periphal HAL ISR disabled
#endif /* configBSP430_SHARE_EUSCIA_ISR */
static void
__attribute__((__interrupt__(EUSCI_A1_VECTOR)))
irq_EUSCI_A1 (void)
{
	euscia_irq(xBSP430euscia_EUSCI_A1);
}
#endif /* configBSP430_EUSCIA_EUSCI_A1_ISR */

#endif /* configBSP430_PERIPH_EUSCI_A1 */

#if configBSP430_PERIPH_EUSCI_A2 - 0
static struct xBSP430eusciaState state_EUSCI_A2_ = {
	.euscia = (xBSP430periphEUSCIA *)__MSP430_BASEADDRESS_EUSCI_A2__
};

xBSP430eusciaHandle const xBSP430euscia_EUSCI_A2 = &state_EUSCI_A2_;

#if configBSP430_PERIPH_EUSCI_A2_ISR - 0
#if ! (configBSP430_SHARE_EUSCIA_ISR - 0)
#error Shared periphal HAL ISR disabled
#endif /* configBSP430_SHARE_EUSCIA_ISR */
static void
__attribute__((__interrupt__(EUSCI_A2_VECTOR)))
irq_EUSCI_A2 (void)
{
	euscia_irq(xBSP430euscia_EUSCI_A2);
}
#endif /* configBSP430_EUSCIA_EUSCI_A2_ISR */

#endif /* configBSP430_PERIPH_EUSCI_A2 */

/* END AUTOMATICALLY GENERATED CODE [hpl_ba_defn] */
/* !BSP430! end=hpl_ba_defn */


static xBSP430eusciaHandle periphToDevice (xBSP430periphHandle periph)
{
/* !BSP430! insert=hpl_hal_demux */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [hpl_hal_demux] */
#if configBSP430_PERIPH_EUSCI_A0 - 0
	if (BSP430_PERIPH_EUSCI_A0 == periph) {
		return xBSP430euscia_EUSCI_A0;
	}
#endif /* configBSP430_PERIPH_EUSCI_A0 */

#if configBSP430_PERIPH_EUSCI_A1 - 0
	if (BSP430_PERIPH_EUSCI_A1 == periph) {
		return xBSP430euscia_EUSCI_A1;
	}
#endif /* configBSP430_PERIPH_EUSCI_A1 */

#if configBSP430_PERIPH_EUSCI_A2 - 0
	if (BSP430_PERIPH_EUSCI_A2 == periph) {
		return xBSP430euscia_EUSCI_A2;
	}
#endif /* configBSP430_PERIPH_EUSCI_A2 */

/* END AUTOMATICALLY GENERATED CODE [hpl_hal_demux] */
/* !BSP430! end=hpl_hal_demux */
	return NULL;
}