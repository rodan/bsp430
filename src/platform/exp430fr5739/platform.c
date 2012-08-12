/* Copyright (c) 2012, Peter A. Bigot
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the software nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <bsp430/platform/exp430fr5739/platform.h>
#include <bsp430/periph/cs.h>
#include <bsp430/utility/led.h>
#include <bsp430/periph/eusci.h>
#include <bsp430/periph/port.h>
#include <bsp430/utility/uptime.h>

#if BSP430_LED - 0
const unsigned char nBSP430led = 8;

/* exp430fr5739 LEDs are PJ.0 to PJ.3 and P4.4 to P4.7.  PJ is not
 * byte addressable, so we need to have a custom implementation of the
 * LED interface. */
void vBSP430ledInitialize_ni (void)
{
  PJDIR |= 0x0F;
  PJOUT &= ~0x0F;
  PJSEL0 &= ~0x0F;
  PJSEL1 &= ~0x0F;
  P3DIR |= 0xF0;
  P3OUT &= ~0xF0;
  P3SEL0 &= ~0xF0;
  P3SEL1 &= ~0xF0;
}

void vBSP430ledSet (int led_idx,
                    int value)
{
  unsigned int bit;
  volatile unsigned int * pxout;
  if (8 <= led_idx) {
    return;
  }
  bit = 1 << led_idx;
  if (4 <= led_idx) {
    pxout = &PBOUT;
  } else {
    pxout = &PJOUT;
  }
  if (value > 0)	{
    *pxout |= bit;
  } else if (value < 0) {
    *pxout ^= bit;
  } else {
    *pxout &= ~bit;
  }
}
#endif /* BSP430_LED */

int
iBSP430platformConfigurePeripheralPins_ni (tBSP430periphHandle device, int enablep)
{
  unsigned int bits = 0;
  unsigned int pba = 0;
  volatile sBSP430hplPORT_5XX_8 * hpl;

  if (BSP430_PERIPH_LFXT1 == device) {
    /* NB: Only XIN (PJ.4) needs to be configured; XOUT follows
     * it. */
    bits = BIT4;
    if (enablep) {
      PJSEL0 |= bits;
    } else {
      PJOUT &= ~bits;
      PJDIR |= bits;
      PJSEL0 &= ~bits;
    }
    PJSEL1 &= ~bits;
    return 0;
  }
#if configBSP430_PERIPH_EXPOSED_CLOCKS - 0
  else if (BSP430_PERIPH_EXPOSED_CLOCKS == device) {
    bits = BIT0 | BIT1 | BIT2;
    PJDIR |= bits;
    PJSEL1 &= ~bits;
    if (enablep) {
      PJSEL0 |= bits;
    } else {
      PJOUT &= ~bits;
      PJSEL0 &= ~bits;
    }
    return 0;
  }
#endif /* configBSP430_PERIPH_EXPOSED_CLOCKS */
#if configBSP430_HPL_EUSCI_A0 - 0
  else if (BSP430_PERIPH_EUSCI_A0 == device) {
    bits = BIT0 | BIT1;
    pba = BSP430_PERIPH_PORT2_BASEADDRESS_;
    if (! enablep) {
      P2DIR |= bits;
      P2OUT &= ~bits;
    }
  }
#endif /* configBSP430_HPL_EUSCI_A0 */
#if configBSP430_HPL_EUSCI_A1 - 0
  else if (BSP430_PERIPH_EUSCI_A1 == device) {
    bits = BIT5 | BIT6;
    pba = BSP430_PERIPH_PORT2_BASEADDRESS_;
    return 0;
  }
#endif /* configBSP430_HPL_EUSCI_A1 */
#if configBSP430_HPL_EUSCI_B0 - 0
  else if (BSP430_PERIPH_EUSCI_B0 == device) {
    bits = BIT6 | BIT7;
    pba = BSP430_PERIPH_PORT1_BASEADDRESS_;
    P1SEL0 &= ~BIT3;
    P2SEL0 &= ~BIT2;
    if (enablep) {
      P1SEL1 |= BIT3;
      P2SEL1 |= BIT2;
    } else {
      P1OUT &= ~BIT3;
      P2OUT &= ~BIT2;
      P1DIR |= BIT3;
      P2DIR |= BIT2;
      P1SEL1 &= ~BIT3;
      P2SEL1 &= ~BIT2;
    }
  }
#endif /* configBSP430_HPL_EUSCI_B0 */
  if (0 == pba) {
    return -1;
  }
  hpl = (volatile sBSP430hplPORT_5XX_8 *)pba;
  hpl->sel0 &= ~bits;
  if (enablep) {
    hpl->sel1 |= bits;
  } else {
    hpl->out &= ~bits;
    hpl->dir |= bits;
    hpl->sel1 &= ~bits;
  }
  return 0;
}

const char *
xBSP430platformPeripheralHelp (tBSP430periphHandle device)
{
  if (BSP430_PERIPH_LFXT1 == device) {
    return "XIN=PJ.4, XOUT=PJ.5";
  }
#if configBSP430_PERIPH_EXPOSED_CLOCKS - 0
  if (BSP430_PERIPH_EXPOSED_CLOCKS == device) {
    return "Test points below LED1-3: SMCLK on TP10; MCLK on TP11; ACLK on TP12";
  }
#endif /* configBSP430_PERIPH_EXPOSED_CLOCKS */
#if configBSP430_HPL_EUSCI_A0 - 0
  if (BSP430_PERIPH_EUSCI_A0 == device) {
    return "MOSI/TXD=P2.0; MISO/RXD=P2.1";
  }
#endif /* configBSP430_HPL_EUSCI_A0 */
#if configBSP430_HPL_EUSCI_A1 - 0
  if (BSP430_PERIPH_EUSCI_A1 == device) {
    return "MOSI/TXD=P2.5; MISO/RXD=P2.6";
  }
#endif /* configBSP430_HPL_EUSCI_A1 */
#if configBSP430_HPL_EUSCI_B0 - 0
  if (BSP430_PERIPH_EUSCI_B0 == device) {
    return "STE=P1.3; MOSI/SDA=P1.6; MISO/SCL=P1.7; CLK=P2.2";
  }
#endif /* configBSP430_HPL_EUSCI_B0 */
  return NULL;
}

void
vBSP430platformSpinForJumper_ni (void)
{
  int bit = 0;
  /* P4.0 input with pullup */
  P4DIR &= ~BIT0;
  P4REN |= BIT0;
  P4OUT |= BIT0;
  vBSP430ledInitialize_ni();
  while (! (P4IN & BIT0)) {
    vBSP430ledSet(bit, -1);
    vBSP430ledSet(7-bit, -1);
    BSP430_CORE_WATCHDOG_CLEAR();
    BSP430_CORE_DELAY_CYCLES(BSP430_CLOCK_NOMINAL_MCLK_HZ / 10);
    vBSP430ledSet(bit, -1);
    vBSP430ledSet(7-bit, -1);
    if (4 == ++bit) {
      bit = 0;
    }
  }
  /* Restore P4.0 */
  P4DIR |= BIT0;
  P4REN &= ~BIT0;
}

void vBSP430platformInitialize_ni (void)
{
  int crystal_ok = 0;
  (void)crystal_ok;

#if ! (configBSP430_CORE_SUPPORT_WATCHDOG - 0)
  /* Hold off watchdog */
  WDTCTL = WDTPW | WDTHOLD;
#endif /* configBSP430_CORE_SUPPORT_WATCHDOG */

#if (BSP430_PLATFORM_BOOT_CONFIGURE_LEDS - 0) && (BSP430_LED - 0)
  vBSP430ledInitialize_ni();
#endif /* BSP430_PLATFORM_BOOT_CONFIGURE_LEDS */

#if BSP430_PLATFORM_BOOT_CONFIGURE_LFXT1 - 0
  crystal_ok = iBSP430clockConfigureLFXT1_ni(1, (BSP430_PLATFORM_BOOT_LFXT1_DELAY_SEC * BSP430_CLOCK_PUC_MCLK_HZ) / BSP430_CLOCK_LFXT1_STABILIZATION_DELAY_CYCLES);
#endif /* BSP430_PLATFORM_BOOT_CONFIGURE_LFXT1 */

#if BSP430_PLATFORM_BOOT_CONFIGURE_CLOCKS - 0
  iBSP430clockConfigureACLK_ni(BSP430_PLATFORM_BOOT_ACLKSRC);
  ulBSP430clockConfigureMCLK_ni(BSP430_CLOCK_NOMINAL_MCLK_HZ);
  iBSP430clockConfigureSMCLKDividingShift_ni(BSP430_CLOCK_NOMINAL_SMCLK_DIVIDING_SHIFT);
#if configBSP430_CORE_DISABLE_FLL - 0
  __bis_status_register(SCG0);
#endif /* configBSP430_CORE_DISABLE_FLL */
#endif /* BSP430_PLATFORM_BOOT_CONFIGURE_CLOCKS */

#if BSP430_UPTIME - 0
  vBSP430uptimeStart_ni();
#endif /* BSP430_UPTIME */
}
