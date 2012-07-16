/* Copyright (c) 2012, Peter A. Bigot <bigotp@acm.org>
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

#include <bsp430/platform.h>
#include <bsp430/periph/ucs.h>
#include "FreeRTOS.h"
#include "task.h"

/* Mask for SELA bits in UCSCTL4 */
#define SELA_MASK (SELA0 | SELA1 | SELA2)

/* Frequency measurement occurs over this duration when determining
 * whether trim is required.  The number of SMCLK ticks in an ACLK
 * period is the target frequency divided by 32768; accumulating over
 * multiple ACLK periods decreases the measurement error.  At a target
 * frequency of 2^25 (32 MiHz) the tick count for a single period
 * might require 11 bits to represent, so do not exceed 32 lest the
 * 16-bit delta value overflow.  Select a value so that the number of
 * ticks within the sample period is some small (~3) multiple of
 * TRIM_TOLERANCE_DIVISOR. */
#define TRIM_SAMPLE_PERIOD_ACLK 8

/* Tolerance for SMCLK ticks within a trim sample period.  The target
 * frequency count is divided by this number; if the measured
 * frequency count is not within that distance of the target, the FLL
 * is enabled for a short duration.  512 is about 0.2% */
#define TRIM_TOLERANCE_DIVISOR 512

/* The target frequency expressed as the number of SMCLK ticks
 * expected within a trim sample period. */
static uint16_t targetFrequency_tsp_;

/* The last calculated trim frequency */
static unsigned long lastTrimFrequency_Hz_;

unsigned long
ulBSP430ucsTrimFLLFromISR ()
{
	short taps_left = 32;
	unsigned short last_ctl0;
	uint16_t tolerance_tsp;
	uint16_t current_frequency_tsp = 0;

	last_ctl0 = ~0;
	tolerance_tsp = targetFrequency_tsp_ / TRIM_TOLERANCE_DIVISOR;
	while (0 < taps_left--) {
		int i;
		unsigned int c0 = 0;
		unsigned int c1;
		uint16_t abs_freq_err_tsp;

		/* Capture the SMCLK ticks between adjacent ACLK ticks */
		TB0CTL = TASSEL__SMCLK | MC__CONTINOUS | TBCLR;
		TB0CCTL6 = CM_2 | CCIS_1 | CAP | SCS;
		/* NOTE: CCIFG seems to be set immediately on the second and
		 * subsequent iterations.  Flush the first capture. */
        while (! (TB0CCTL6 & CCIFG)) {
          ; /* nop */
        }
		for (i = 0; i <= TRIM_SAMPLE_PERIOD_ACLK; ++i) {
			TB0CCTL6 &= ~CCIFG;
			while (! (TB0CCTL6 & CCIFG)) {
				; /* nop */
			}
			if (0 == i) {
				c0 = TB0CCR6;
			}
		}
        c1 = TB0CCR6;
		TB0CTL = 0;
		TB0CCTL6 = 0;
		current_frequency_tsp = (c0 > c1) ? (c0 - c1) : (c1 - c0);
		if (current_frequency_tsp > targetFrequency_tsp_) {
			abs_freq_err_tsp = current_frequency_tsp - targetFrequency_tsp_;
		} else {
			abs_freq_err_tsp = targetFrequency_tsp_ - current_frequency_tsp;
		}
#if 0
		cprintf("RSEL %u DCO %u MOD %u current %u target %u tol %u err %u ; ctl0 %04x last %04x\n",
			   (UCSCTL1 >> 4) & 0x07, (UCSCTL0 >> 8) & 0x1F, (UCSCTL0 >> 3) & 0x1F,
			   current_frequency_tsp, targetFrequency_tsp_, tolerance_tsp, abs_freq_err_tsp,
			   UCSCTL0, last_ctl0);
#endif
		if ((abs_freq_err_tsp <= tolerance_tsp)
			|| (UCSCTL0 == last_ctl0)) {
#if 0
			cprintf("terminate tap %u error %u ctl0 %04x was %04x\n",
				   taps_left, abs_freq_err_tsp, UCSCTL0, last_ctl0);
#endif
			break;
		}
#if 0
		cprintf("running fll, error %u\n", abs_freq_err_tsp);
#endif
		/* Save current DCO/MOD values, then let FLL run for 32 REFCLK
		 * ticks (potentially trying each modulation within one
		 * tap) */
		last_ctl0 = UCSCTL0;
		TB0CTL = TASSEL__ACLK | MC__CONTINOUS | TBCLR;
		__bic_status_register(SCG0);
		TB0CCTL0 = 0;
		TB0CCR0 = TB0R + 32;
		while (! (TB0CCTL0 & CCIFG)) {
			/* nop */
		}
		__bis_status_register(SCG0);
		/* Delay another 1..2 ACLK cycles for the integrator to fully
		 * update. */
		TB0CCTL0 &= ~CCIFG;
		TB0CCR0 = TB0R + 2;
		while (! (TB0CCTL0 & CCIFG)) {
			/* nop */
		}
		TB0CTL = 0;
		TB0CCTL0 = 0;
	}
	lastTrimFrequency_Hz_ = current_frequency_tsp * (32768UL / TRIM_SAMPLE_PERIOD_ACLK);
	lastTrimFrequency_Hz_ <<= configBSP430_CLOCK_SMCLK_DIVIDING_SHIFT;
	return lastTrimFrequency_Hz_;
}

unsigned long
ulBSP430clockMCLK_Hz ()
{
	return lastTrimFrequency_Hz_;
}

unsigned long
ulBSP430clockSMCLK_Hz ()
{
	return lastTrimFrequency_Hz_ >> configBSP430_CLOCK_SMCLK_DIVIDING_SHIFT;
}

unsigned short
usBSP430clockACLK_Hz ()
{
	if ((SELA__XT1CLK == (UCSCTL4 & (SELA0 | SELA1 | SELA2)))
		&& !(SFRIFG1 & OFIFG)) {
		return 32768U;
	}
	return 10000;
}

int
iBSP430clockConfigureXT1 (int enablep,
						  int loop_limit)
{
	int loop_delta;
	int rc;
	
	rc = iBSP430platformConfigurePeripheralPins(BSP430_PERIPH_XT1, enablep);
	if ((0 != rc) || (! enablep)) {
		return rc;
	}
	loop_delta = (0 < loop_limit) ? 1 : 0;

	/* Low frequency XT1 needed; XT2 off.  Spin at high drive to
	 * stability, then drop back. */
	UCSCTL6 = XT2OFF | XT1DRIVE_3 | XCAP_0;
	do {
		UCSCTL7 &= ~XT1LFOFFG;
		loop_limit -= loop_delta;
		__delay_cycles(configBSP430_CLOCK_XT1_STABILIZATION_DELAY_CYCLES);

	} while ((UCSCTL7 & XT1LFOFFG) && (0 != loop_limit));
	UCSCTL6 &= ~XT1DRIVE_3;

	rc = !(UCSCTL7 & XT1LFOFFG);
	if (! rc) {
		UCSCTL6 |= XT1OFF;
		(void)iBSP430platformConfigurePeripheralPins(BSP430_PERIPH_XT1, 0);
	}
	return rc;
}


int iBSP430ucsConfigureACLK (unsigned int sela)
{
	if (sela & ~SELA_MASK) {
		return -1;
	}
	UCSCTL4 = (UCSCTL4 & ~SELA_MASK) | sela;
	return 0;
}

unsigned long
ulBSP430ucsConfigure ( unsigned long ulFrequency_Hz,
					   short sRSEL )
{
	/* The values in this table should be roughly half the minimum
	 * frequency for the specified RSEL with DCOx=31 and MODx=0,
	 * as taken from the device-specific data sheet. */
	static const unsigned long pulRSELCutoffs [] = {
#if defined(__MSP430F5438__) || defined(__MSP430F5438A__)
		700000UL / 2,			/* RSEL0 */
		1470000UL / 2,			/* RSEL1 */
		3170000UL / 2,			/* RSEL2 */
		6070000UL / 2,			/* RSEL3 */
		12300000UL / 2,			/* RSEL4 */
		23700000UL / 2,			/* RSEL5 */
		39000000UL / 2,			/* RSEL6 */
#else
#endif
		UINT32_MAX
	};
	unsigned portBASE_TYPE ctl1;
	unsigned portBASE_TYPE ctl2;
	unsigned long ulReturn;
	
	/* If not told what RSEL to use, pick the one appropriate for the
	 * target frequency. */
	if ((0 > sRSEL) || (7 < sRSEL)) {
		sRSEL = 0;
		while (pulRSELCutoffs[ sRSEL ] < ulFrequency_Hz) {
			++sRSEL;
		}
	}

	BSP430_ENTER_CRITICAL();

	/* Require XT1 valid and use it as ACLK source */
	if (UCSCTL7 & XT1LFOFFG) {
		(void)iBSP430clockConfigureXT1 (1, -1);
	}
	iBSP430ucsConfigureACLK(SELA__XT1CLK);

	/* All supported frequencies can be efficiently achieved using
	 * FFLD set to /2 (>> 1) and FLLREFDIV set to /1 (>> 0).
	 * FLLREFCLK will always be XT1CLK.  FLLN is calculated from
	 * ulFrequency_Hz. */
	ctl1 = sRSEL * DCORSEL0;
	ctl2 = FLLD_1 | ((((ulFrequency_Hz << 1) / (32768 >> 0)) >> 1) - 1);

	__bis_status_register(SCG0);
	UCSCTL0 = 0;
	UCSCTL1 = ctl1;
	UCSCTL2 = ctl2;
	UCSCTL3 = SELREF__XT1CLK | FLLREFDIV_0;
	UCSCTL4 = (UCSCTL4 & SELA_MASK) | SELS__DCOCLKDIV | SELM__DCOCLKDIV;

	targetFrequency_tsp_ = ulFrequency_Hz / (32768 / TRIM_SAMPLE_PERIOD_ACLK);
	targetFrequency_tsp_ >>= configBSP430_CLOCK_SMCLK_DIVIDING_SHIFT;

	ulReturn = ulBSP430ucsTrimFLLFromISR();

	/* Spin until DCO stabilized */
	do {
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
		SFRIFG1 &= ~OFIFG;
	} while (UCSCTL7 & DCOFFG);

	UCSCTL5 = (0x70 & (configBSP430_CLOCK_SMCLK_DIVIDING_SHIFT << 4));

#if ! (portDISABLE_FLL - 0)
	/* Turn FLL back on */
	__bic_status_register(SCG0);
#endif
	BSP430_EXIT_CRITICAL();

	return ulReturn;
}