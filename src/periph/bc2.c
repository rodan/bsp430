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
#include <bsp430/periph/bc2.h>

/** The last frequency configured using #ulBSP430clockConfigureMCLK_ni */
static unsigned long configuredMCLK_Hz = 1100000UL;

#define SELS_MASK (SELS)
#define SELM_MASK (SELM0 | SELM1)
#define DIVM_MASK (DIVM0 | DIVM1)
#define DIVS_MASK (DIVS0 | DIVS1)

int
iBSP430clockConfigureXT1_ni (int enablep,
                             int loop_limit)
{
  int loop_delta;
  int rc = 0;

  if (0 != loop_limit) {
    rc = iBSP430platformConfigurePeripheralPins_ni(BSP430_PERIPH_XT1, enablep);
    if ((0 != rc) || (! enablep)) {
      return rc;
    }
    loop_delta = (0 < loop_limit) ? 1 : 0;

    /* See whether the crystal is populated and functional.  Do
     * this with the DCO reset to the power-up configuration,
     * where clock should be nominal 1 MHz. */
    BCSCTL3 = XCAP_1;
    do {
      BSP430_CLOCK_LFXT1_CLEAR_FAULT();
      loop_limit -= loop_delta;
      BSP430_CORE_WATCHDOG_CLEAR();
      __delay_cycles(BSP430_CLOCK_LFXT1_STABILIZATION_DELAY_CYCLES);

    } while ((BSP430_CLOCK_LFXT1_IS_FAULTED()) && (0 != loop_limit));
    rc = ! BSP430_CLOCK_LFXT1_IS_FAULTED();
  }
  if (! rc) {
    BCSCTL3 = LFXT1S_2;
    (void)iBSP430platformConfigurePeripheralPins_ni(BSP430_PERIPH_XT1, 0);
  }
  return rc;
}

unsigned char
ucBSP430bc2Configure_ni (unsigned char ucDCOCTL,
                         unsigned char ucBCSCTL1,
                         unsigned char ucBCSCTL2,
                         unsigned char ucBCSCTL3)
{
  unsigned char ucCrystalOK = 0;

  BCSCTL3 = ucBCSCTL3;
  if (! (BCSCTL3 & LFXT1S1)) {
    ucCrystalOK = iBSP430clockConfigureXT1_ni(1, 10);
  }
  /* Select lowest DCOx and MODx prior to configuring */
  DCOCTL = 0;
  /* Set range */
  BCSCTL1 = ucBCSCTL1;
  /* Set DCO step and modulation */
  DCOCTL = ucDCOCTL;
  /* Set clock dividers */
  BCSCTL2 = ucBCSCTL2;

  return ucCrystalOK;
}

int
iBSP430clockSMCLKDividingShift_ni (void)
{
  int divs;

  /* Assume that the source for both MCLK and SMCLK is the same, but
   * account for a potential DIVM. */
  divs = (BCSCTL2 & DIVS_MASK) / DIVS0;
  divs -= (BCSCTL2 & DIVM_MASK) / DIVM0;
  return divs;
}

int
iBSP430clockConfigureSMCLKDividingShift_ni (int shift_pos)
{
  unsigned char bcsctl2 = BCSCTL2;

  /* Set SMCLK source to the same as MCLK */
  if (SELM1 & bcsctl2) {
    bcsctl2 |= SELS;
  } else {
    bcsctl2 &= ~SELS;
  }
  /* Adjust for division of MCLK */
  shift_pos += (bcsctl2 & DIVM_MASK) / DIVM0;
  BCSCTL2 = (bcsctl2 & ~DIVS_MASK) | (DIVS_MASK & (shift_pos * DIVS0));
  return iBSP430clockSMCLKDividingShift_ni();
}

unsigned short
usBSP430clockACLK_Hz_ni (void)
{
  return BSP430_CLOCK_NOMINAL_ACLK_HZ;
}

unsigned long
ulBSP430clockMCLK_Hz_ni (void)
{
  return configuredMCLK_Hz;
}

#include <stdio.h>

unsigned long
ulBSP430clockConfigureMCLK_ni (unsigned long mclk_Hz)
{
  unsigned char dcoctl;
  unsigned char bcsctl1;
  unsigned long error_Hz;
  long freq_Hz;

  /* Power-up defaults */
  dcoctl = 0x60;
  bcsctl1 = 0x87;
  freq_Hz = 1100000UL;

  /* Calculate absolute error from _freq_Hz to target */
#define ERROR_HZ(_freq_Hz) ((mclk_Hz < _freq_Hz) ? (_freq_Hz - mclk_Hz) : (mclk_Hz - _freq_Hz))
  error_Hz = ERROR_HZ(freq_Hz);

  /* Test a candidate to see if it's better than what we've got now */
#define TRY_FREQ(_tag, _cand_Hz) do {                   \
    unsigned long cand_error_Hz = ERROR_HZ(_cand_Hz);   \
    if (cand_error_Hz < error_Hz) {                     \
      dcoctl = CALDCO_##_tag;                           \
      bcsctl1 = CALBC1_##_tag;                          \
      freq_Hz = _cand_Hz;                               \
      error_Hz = cand_error_Hz;                         \
    }                                                   \
  } while (0)

  /* Candidate availability is MCU-specific and can be determined by
   * checking for a corresponding preprocessor definition */
#if defined(CALDCO_1MHZ_)
  TRY_FREQ(1MHZ, 1000000UL);
#endif /* CALDCO_1MHZ */
#if defined(CALDCO_8MHZ_)
  TRY_FREQ(8MHZ, 8000000UL);
#endif /* CALDCO_8MHZ */
#if defined(CALDCO_12MHZ_)
  TRY_FREQ(12MHZ, 12000000UL);
#endif /* CALDCO_12MHZ */
#if defined(CALDCO_16MHZ_)
  TRY_FREQ(16MHZ, 16000000UL);
#endif /* CALDCO_16MHZ */

#undef TRY_FREQ
#undef ERROR_HZ

  DCOCTL = 0;
  BCSCTL1 = bcsctl1;
  DCOCTL = dcoctl;
  /* SELM = DCOCLK; DIVM = /1 */
  BCSCTL2 &= ~(SELM_MASK | DIVM_MASK);
  configuredMCLK_Hz = freq_Hz;

  return configuredMCLK_Hz;
}
