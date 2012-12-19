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

#ifndef BSP430_PLATFORM_EXP430F5529_PLATFORM_H
#define BSP430_PLATFORM_EXP430F5529_PLATFORM_H

/** @file
 *
 * @brief Platform-specific include for <a href="http://www.ti.com/tool/msp-exp430f5529">MSP-EXP430F5529</a>
 *
 * The following platform-specific features are supported: <ul>
 *
 * <li> #vBSP430platformSpinForJumper_ni The jumper for this platform
 * is P7.7, located at the bottom of header J5 on the right of the
 * board below the JTAG header.  Place the jumper between GND and
 * P7.7.
 *
 * <li> #BSP430_PERIPH_EXPOSED_CLOCKS ACLK is made visible on P1.0
 * which can be found on the J12 or RF1 header.  MCLK is made visible
 * on P7.7 which is on header J5 below the JTAG header.  SMCLK is made
 * visible on P2.2 which is not brought out to any accessible
 * location.
 *
 * </ul>
 *
 * @homepage http://github.com/pabigot/bsp430
 * @copyright Copyright 2012, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

/** Unconditionally define this, so as to produce errors if there is a
 * conflict in definition. */
#define BSP430_PLATFORM_EXP430F5529 1

/* Enable if requested (ez430 serial needs it) */
#if configBSP430_PLATFORM_SPIN_FOR_JUMPER - 0
#define BSP430_PLATFORM_SPIN_FOR_JUMPER 1
#endif /* configBSP430_PLATFORM_SPIN_FOR_JUMPER */

/* Available button definitions */
#define BSP430_PLATFORM_BUTTON0_PORT_PERIPH_HANDLE BSP430_PERIPH_PORT1
#define BSP430_PLATFORM_BUTTON0_PORT_BIT BIT7
#define BSP430_PLATFORM_BUTTON1_PORT_PERIPH_HANDLE BSP430_PERIPH_PORT2
#define BSP430_PLATFORM_BUTTON1_PORT_BIT BIT2

/* Standard LED colors */
#define BSP430_LED_RED 0
#define BSP430_LED_ORANGE 1
#define BSP430_LED_GREEN 2
#define BSP430_LED_BLUE 3
#define BSP430_LED_BLUE1 4
#define BSP430_LED_BLUE2 5
#define BSP430_LED_BLUE3 6
#define BSP430_LED_BLUE4 7

/* How to use ACLK as a capture/compare input source */
/* Settings for TB0: T0B6 ccis=1 ; clk P7.7 ; cc0 P5.6 ; cc1 P5.7 */
#ifndef BSP430_TIMER_CCACLK_ACLK_CC
/* NB: Check against BSP430_TIMER_CCACLK_PERIPH_CPPID in bsp430_config.h */
#define BSP430_TIMER_CCACLK_ACLK_CC 6
#endif /* BSP430_TIMER_CCACLK_ACLK_CC */
#ifndef BSP430_TIMER_CCACLK_ACLK_CCIS
/* NB: Check against BSP430_TIMER_CCACLK_PERIPH_CPPID in bsp430_config.h */
#define BSP430_TIMER_CCACLK_ACLK_CCIS CCIS_1
#endif /* BSP430_TIMER_CCACLK_ACLK_CCIS */
#ifndef BSP430_TIMER_CCACLK_CLK_PORT_BIT
/* NB: Check against BSP430_TIMER_CCACLK_CLK_PORT_PERIPH_CPPID in bsp430_config.h */
#define BSP430_TIMER_CCACLK_CLK_PORT_BIT BIT7
#endif /* BSP430_TIMER_CCACLK_CLK_PORT_BIT */
#ifndef BSP430_TIMER_CCACLK_CC0_PORT_BIT
/* NB: Check against BSP430_TIMER_CCACLK_CC0_PORT_PERIPH_CPPID in bsp430_config.h */
#define BSP430_TIMER_CCACLK_CC0_PORT_BIT BIT6
#endif /* BSP430_TIMER_CCACLK_CC0_PORT_BIT */
#ifndef BSP430_TIMER_CCACLK_CC1_PORT_BIT
/* NB: Check against BSP430_TIMER_CCACLK_CC1_PORT_PERIPH_CPPID in bsp430_config.h */
#define BSP430_TIMER_CCACLK_CC1_PORT_BIT BIT7
#endif /* BSP430_TIMER_CCACLK_CC1_PORT_BIT */

/* RFEM capabilities */
#if (configBSP430_RFEM - 0)
#define BSP430_RFEM 1
#define BSP430_RFEM_SPI0_PERIPH_HANDLE BSP430_PERIPH_USCI5_B0
/* GDO0: P2.3, CCI0A on TA2.0 */
#define BSP430_RFEM_GDO0_PORT_PERIPH_HANDLE BSP430_PERIPH_PORT2
#define BSP430_RFEM_GDO0_PORT_BIT BIT3
/* GDO0: P3.1, not available as CC input */
#define BSP430_RFEM_GDO1_PORT_PERIPH_HANDLE BSP430_PERIPH_PORT3
#define BSP430_RFEM_GDO1_PORT_BIT BIT1
/* GDO0: P2.4, CCI1A on TA2.1 */
#define BSP430_RFEM_GDO2_PORT_PERIPH_HANDLE BSP430_PERIPH_PORT2
#define BSP430_RFEM_GDO2_PORT_BIT BIT4
#define BSP430_RFEM_SPI0CSn_PORT_PERIPH_HANDLE BSP430_PERIPH_PORT2
#define BSP430_RFEM_SPI0CSn_PORT_BIT BIT6
#endif /* configBSP430_RFEM */

/* Include generic file, in case this is being included directly */
#include <bsp430/platform.h>

#endif /* BSP430_PLATFORM_EXP430F5529_H */
