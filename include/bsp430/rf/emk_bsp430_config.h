/* Copyright 2013-2014, Peter A. Bigot
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

/** @file
 * @brief BSP430 RFEM to EMK configuration directive mapping
 *
 * This file contains automatically-generated maps from RFEM
 * peripheral C preprocessor identifiers to EMK-specific functional
 * peripheral C preprocessor identifiers based on which RF header pins
 * to EMK function pin connections.  The file is automatically
 * included by <bsp430/platform/bsp430_config.h> when
 * #configBSP430_RFEM is enabled, but has no effect unless a specific
 * EMK is also enabled.
 *
 * @homepage http://github.com/pabigot/bsp430
 * @copyright Copyright 2013-2014, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_RF_EMKBSP430CONFIG_H
#define BSP430_RF_EMKBSP430CONFIG_H

#if (configBSP430_RF_TIMER - 0)
#ifndef BSP430_RF_TIMER_PERIPH_CPPID
/* Default timer used for GPIOs in all RFEM connectors is TA0 */
#define BSP430_RF_TIMER_PERIPH_CPPID BSP430_PERIPH_CPPID_TA0
#endif /* BSP430_RF_TIMER_PERIPH_CPPID */
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_TIMER_PERIPH_CPPID
#define BSP430_WANT_CONFIG_HAL_ISR 1
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* configBSP430_RF_TIMER */

/* !BSP430! insert=emk_config emk=cc110xemk tag=cc110x hal=CSn gpio=GDO0,GDO1,GDO2 */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [emk_config] */
#if (configBSP430_RF_CC110XEMK - 0)
#if defined(BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID)
#define BSP430_RF_CC110X_GDO0_PORT_PERIPH_CPPID BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P10_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC110X_GDO0_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P10_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P10_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID)
#define BSP430_RF_CC110X_GDO1_PORT_PERIPH_CPPID BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P20_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC110X_GDO1_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P20_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P20_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID)
#define BSP430_RF_CC110X_GDO2_PORT_PERIPH_CPPID BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC110X_GDO2_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID)
#define BSP430_RF_CC110X_CSn_PORT_PERIPH_CPPID BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID */
/* Request HAL (and HPL) for all GPIO and HAL-enabled ports */
#define BSP430_WANT_CONFIG_HAL 1
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC110X_GDO0_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC110X_GDO1_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC110X_GDO2_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC110X_CSn_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#undef BSP430_WANT_CONFIG_HAL
/* Request HAL for GPIO timers */
#define BSP430_WANT_CONFIG_HAL 1

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC110X_GDO0_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC110X_GDO0_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC110X_GDO0_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC110X_GDO0_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC110X_GDO0_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC110X_GDO0 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC110X_GDO1_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC110X_GDO1_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC110X_GDO1_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC110X_GDO1_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC110X_GDO1_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC110X_GDO1 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC110X_GDO2_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC110X_GDO2_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC110X_GDO2_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC110X_GDO2_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC110X_GDO2_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC110X_GDO2 timer */
#undef BSP430_WANT_CONFIG_HAL
#endif /* configBSP430_RF_CC110XEMK */
/* END AUTOMATICALLY GENERATED CODE [emk_config] */
/* !BSP430! end=emk_config */
/* !BSP430! insert=emk_config emk=cc1125emk tag=cc1125 hal=CSn gpio=GPIO0,GPIO1,GPIO2,GPIO3 */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [emk_config] */
#if (configBSP430_RF_CC1125EMK - 0)
#if defined(BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO0_PORT_PERIPH_CPPID BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P10_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO0_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P10_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P10_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO1_PORT_PERIPH_CPPID BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P20_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO1_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P20_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P20_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO2_PORT_PERIPH_CPPID BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO2_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID)
#define BSP430_RF_CC1125_CSn_PORT_PERIPH_CPPID BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P15_PORT_PERIPH_CPPID)
#define BSP430_RF_CC1125_RESETn_PORT_PERIPH_CPPID BSP430_RFEM_RF2P15_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P15_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P18_PORT_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO3_PORT_PERIPH_CPPID BSP430_RFEM_RF2P18_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P18_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P18_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC1125_GPIO3_TIMER_PERIPH_CPPID BSP430_RFEM_RF2P18_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P18_TIMER_PERIPH_CPPID */
/* Request HAL (and HPL) for all GPIO and HAL-enabled ports */
#define BSP430_WANT_CONFIG_HAL 1
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO0_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO1_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO2_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_CSn_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO3_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#undef BSP430_WANT_CONFIG_HAL
/* Request HPL for all non-GPIO ports */
#define BSP430_WANT_CONFIG_HPL 1
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_RESETn_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#undef BSP430_WANT_CONFIG_HPL
/* Request HAL for GPIO timers */
#define BSP430_WANT_CONFIG_HAL 1

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC1125_GPIO0_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO0_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC1125_GPIO0_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC1125_GPIO0_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC1125_GPIO0_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC1125_GPIO0 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC1125_GPIO1_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO1_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC1125_GPIO1_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC1125_GPIO1_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC1125_GPIO1_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC1125_GPIO1 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC1125_GPIO2_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO2_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC1125_GPIO2_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC1125_GPIO2_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC1125_GPIO2_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC1125_GPIO2 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC1125_GPIO3_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC1125_GPIO3_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC1125_GPIO3_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC1125_GPIO3_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC1125_GPIO3_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC1125_GPIO3 timer */
#undef BSP430_WANT_CONFIG_HAL
#endif /* configBSP430_RF_CC1125EMK */
/* END AUTOMATICALLY GENERATED CODE [emk_config] */
/* !BSP430! end=emk_config */
/* !BSP430! insert=emk_config emk=cc2520emk tag=cc2520 hal=CSn gpio=GPIO0,GPIO1,GPIO2,GPIO3,GPIO4,GPIO5 */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [emk_config] */
#if (configBSP430_RF_CC2520EMK - 0)
#if defined(BSP430_RFEM_RF1P3_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO0_PORT_PERIPH_CPPID BSP430_RFEM_RF1P3_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P3_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P3_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO0_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P3_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P3_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P7_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO1_PORT_PERIPH_CPPID BSP430_RFEM_RF1P7_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P7_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P7_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO1_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P7_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P7_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P9_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO2_PORT_PERIPH_CPPID BSP430_RFEM_RF1P9_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P9_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P9_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO2_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P9_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P9_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_VREG_EN_PORT_PERIPH_CPPID BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO3_PORT_PERIPH_CPPID BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO3_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_CSn_PORT_PERIPH_CPPID BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_SO_PORT_PERIPH_CPPID BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P20_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P15_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_RESETn_PORT_PERIPH_CPPID BSP430_RFEM_RF2P15_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P15_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P18_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO4_PORT_PERIPH_CPPID BSP430_RFEM_RF2P18_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P18_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P18_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO4_TIMER_PERIPH_CPPID BSP430_RFEM_RF2P18_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P18_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P19_PORT_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO5_PORT_PERIPH_CPPID BSP430_RFEM_RF2P19_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P19_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF2P19_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC2520_GPIO5_TIMER_PERIPH_CPPID BSP430_RFEM_RF2P19_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF2P19_TIMER_PERIPH_CPPID */
/* Request HAL (and HPL) for all GPIO and HAL-enabled ports */
#define BSP430_WANT_CONFIG_HAL 1
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO0_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO1_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO2_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO3_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_CSn_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO4_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO5_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#undef BSP430_WANT_CONFIG_HAL
/* Request HPL for all non-GPIO ports */
#define BSP430_WANT_CONFIG_HPL 1
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_VREG_EN_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_SO_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_RESETn_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#undef BSP430_WANT_CONFIG_HPL
/* Request HAL for GPIO timers */
#define BSP430_WANT_CONFIG_HAL 1

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC2520_GPIO0_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO0_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC2520_GPIO0_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC2520_GPIO0_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC2520_GPIO0_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC2520_GPIO0 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC2520_GPIO1_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO1_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC2520_GPIO1_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC2520_GPIO1_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC2520_GPIO1_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC2520_GPIO1 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC2520_GPIO2_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO2_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC2520_GPIO2_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC2520_GPIO2_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC2520_GPIO2_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC2520_GPIO2 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC2520_GPIO3_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO3_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC2520_GPIO3_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC2520_GPIO3_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC2520_GPIO3_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC2520_GPIO3 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC2520_GPIO4_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO4_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC2520_GPIO4_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC2520_GPIO4_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC2520_GPIO4_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC2520_GPIO4 timer */

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC2520_GPIO5_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC2520_GPIO5_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC2520_GPIO5_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC2520_GPIO5_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC2520_GPIO5_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC2520_GPIO5 timer */
#undef BSP430_WANT_CONFIG_HAL
#endif /* configBSP430_RF_CC2520EMK */
/* END AUTOMATICALLY GENERATED CODE [emk_config] */
/* !BSP430! end=emk_config */
/* !BSP430! insert=emk_config emk=cc3000em tag=cc3000 hal=CSn gpio=IRQn */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [emk_config] */
#if (configBSP430_RF_CC3000EM - 0)
#if defined(BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID)
#define BSP430_RF_CC3000_PWR_EN_PORT_PERIPH_CPPID BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P10_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID)
#define BSP430_RF_CC3000_IRQn_PORT_PERIPH_CPPID BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_PORT_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID)
#define BSP430_RF_CC3000_IRQn_TIMER_PERIPH_CPPID BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P12_TIMER_PERIPH_CPPID */
#if defined(BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID)
#define BSP430_RF_CC3000_CSn_PORT_PERIPH_CPPID BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID
#endif /* BSP430_RFEM_RF1P14_PORT_PERIPH_CPPID */
/* Request HAL (and HPL) for all GPIO and HAL-enabled ports */
#define BSP430_WANT_CONFIG_HAL 1
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC3000_IRQn_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC3000_CSn_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#undef BSP430_WANT_CONFIG_HAL
/* Request HPL for all non-GPIO ports */
#define BSP430_WANT_CONFIG_HPL 1
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC3000_PWR_EN_PORT_PERIPH_CPPID
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_PERIPH_CPPID
#undef BSP430_WANT_CONFIG_HPL
/* Request HAL for GPIO timers */
#define BSP430_WANT_CONFIG_HAL 1

#if (configBSP430_RF_TIMER - 0) && defined(BSP430_RF_CC3000_IRQn_TIMER_PERIPH_CPPID)
#define BSP430_WANT_PERIPH_CPPID BSP430_RF_CC3000_IRQn_TIMER_PERIPH_CPPID
#if 0 == BSP430_RF_CC3000_IRQn_TIMER_CCIDX
#define BSP430_WANT_CONFIG_HAL_CC0_ISR 1
#else /* BSP430_RF_CC3000_IRQn_TIMER_CCIDX */
#define BSP430_WANT_CONFIG_HAL_ISR 1
#endif /* BSP430_RF_CC3000_IRQn_TIMER_CCIDX */
#include <bsp430/periph/want_.h>
#undef BSP430_WANT_CONFIG_HAL_ISR
#undef BSP430_WANT_CONFIG_HAL_CC0_ISR
#undef BSP430_WANT_PERIPH_CPPID
#endif /* BSP430_RF_CC3000_IRQn timer */
#undef BSP430_WANT_CONFIG_HAL
#endif /* configBSP430_RF_CC3000EM */
/* END AUTOMATICALLY GENERATED CODE [emk_config] */
/* !BSP430! end=emk_config */

#endif /* BSP430_RF_EMKBSP430CONFIG_H */
