/* Copyright 2012-2013, Peter A. Bigot
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
 *
 * @brief A generic console print capability.
 *
 * cprintf() is like @c printf.
 *
 * In the default configuration with interrupt-driven transmission
 * disabled, it disables interrupts while operating to ensure that
 * interleaved messages do not occur, transmits with direct UART
 * writes, and is "safe" for call from within interrupt handlers.
 *
 * cputs() and cputchars() are provided where the complexity of printf
 * is not required but atomic output is desired.  Other routines
 * permit display of NUL-terminated plain text without a newline
 * (cputtext_ni()), plain text without termination (cputchars_ni()),
 * single characters (cputchar_ni()), and integers (cputi_ni(),
 * cputu_ni(), cputl_ni(), cputul_ni()) without incurring the stack
 * overhead of printf, which can be quite high (on the order of 100
 * bytes if 64-bit integer support is included).  These all assume
 * that interrupts are disabled when called.
 *
 * All these routines are safe to call even if the console was not
 * initialized, or its initialization failed, or it is temporarily
 * disabled: in that situation, they simply return immediately.
 *
 * As the console has proved to be extremely useful, it has also been
 * enhanced with interrupt-driven transmision capabilities.  By
 * configuring #BSP430_CONSOLE_TX_BUFFER_SIZE to a positive value all
 * console output routines will place their output into the buffer.
 * If insufficient room remains, they will block.
 *
 * @warning The console routines are not safe to call from interrupts
 * when #BSP430_CONSOLE_TX_BUFFER_SIZE has been configured to enable
 * interrupt-driven output.  If, at runtime, you determine you need to
 * do console output without interrupts, use
 * iBSP430consoleTransmitUseInterrupts_ni() to enable and disable
 * interrupt-driven transmission.
 *
 * @homepage http://github.com/pabigot/bsp430
 * @copyright Copyright 2012-2013, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_UTILITY_CONSOLE_H
#define BSP430_UTILITY_CONSOLE_H

#include <bsp430/serial.h>
#include <bsp430/platform.h>
#include <stdarg.h>

/** @def configBSP430_CONSOLE
 *
 * Define to a true value to request that a serial handle be
 * identified to serve as a system console.
 *
 * See #BSP430_CONSOLE_SERIAL_PERIPH_CPPID for information about which
 * serial peripheral will be used for this capability.
 *
 * @cppflag
 * @affects #BSP430_CONSOLE
 * @defaulted
 */
#ifndef configBSP430_CONSOLE
#define configBSP430_CONSOLE 0
#endif /* configBSP430_CONSOLE */

/** @def BSP430_CONSOLE
 *
 * Defined to a true value if #BSP430_CONSOLE_SERIAL_PERIPH_CPPID has
 * been provided, making the console infrastructure available.
 *
 * @dependency #configBSP430_CONSOLE
 * @platformdefault
 */
#if defined(BSP430_DOXYGEN)
#define BSP430_CONSOLE include <bsp430/platform.h>
#endif /* BSP430_DOXYGEN */

/** @def BSP430_CONSOLE_SERIAL_PERIPH_CPPID
 *
 * Define to the preprocessor-compatible identifier for the peripheral
 * that should be used by platform-agnostic programs to create the
 * console, for example #BSP430_PERIPH_CPPID_USCI5_A0.
 *
 * The define must appear in the @ref bsp430_config subsystem so that
 * functional resource requests are correctly propagated to the
 * underlying resource instances.  A default is provided based on the
 * platform or available serial peripherals.
 *
 * @dependency #BSP430_CONSOLE
 * @platformdefault
 * @affects #BSP430_CONSOLE_SERIAL_PERIPH_HANDLE */
#if defined(BSP430_DOXYGEN)
#define BSP430_CONSOLE_SERIAL_PERIPH_CPPID include "bsp430_config.h"
#endif /* BSP430_DOXYGEN */

/** @def BSP430_CONSOLE_SERIAL_PERIPH_HANDLE
 *
 * The peripheral handle that should be used by platform-agnostic
 * programs to create the console.  This derives directly from
 * #BSP430_CONSOLE_SERIAL_PERIPH_CPPID, but is a serial peripheral
 * handle suitable for use in code.
 *
 * The corresponding HAL and ISR features are automatically enabled
 * for this peripheral.
 *
 * @dependency #BSP430_CONSOLE_SERIAL_PERIPH_CPPID
 * @platformdefault */
#if defined(BSP430_DOXYGEN)
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE derived platform or application specific
/* !BSP430! instance=@serial functional=console_serial subst=functional insert=periph_sethandle */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [periph_sethandle] */

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI_A0
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI_A0

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI_A1
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI_A1

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI_B0
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI_B0

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI_B1
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI_B1

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_A0
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_A0

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_A1
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_A1

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_A2
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_A2

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_A3
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_A3

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_B0
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_B0

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_B1
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_B1

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_B2
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_B2

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_USCI5_B3
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_USCI5_B3

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_EUSCI_A0
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_EUSCI_A0

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_EUSCI_A1
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_EUSCI_A1

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_EUSCI_A2
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_EUSCI_A2

#elif BSP430_CONSOLE_SERIAL_PERIPH_CPPID == BSP430_PERIPH_CPPID_EUSCI_B0
#define BSP430_CONSOLE_SERIAL_PERIPH_HANDLE BSP430_PERIPH_EUSCI_B0
/* END AUTOMATICALLY GENERATED CODE [periph_sethandle] */
/* !BSP430! end=periph_sethandle */
#endif /* BSP430_CONSOLE_SERIAL_PERIPH_HANDLE */

/** @def BSP430_CONSOLE_BAUD_RATE
 *
 * The baud rate that should be used for the console.  This may be
 * overridden in a platform header or by an application configuration.
 *
 * @defaulted */
#ifndef BSP430_CONSOLE_BAUD_RATE
#define BSP430_CONSOLE_BAUD_RATE 9600
#endif /* BSP430_CONSOLE_BAUD_RATE */

/** @def BSP430_CONSOLE_RX_BUFFER_SIZE
 *
 * Define this to the size of a buffer to be used for interrupt-driven
 * console input.  The value must not exceed 254, and buffer
 * management is most efficient if the value is a power of 2.
 *
 * If this has a value of zero, character input is not interrupt
 * driven.  cgetchar_ni() will return the most recently received
 * character, if any, and cpeekchar_ni() will not be available.
 *
 * @defaulted */
#ifndef BSP430_CONSOLE_RX_BUFFER_SIZE
#define BSP430_CONSOLE_RX_BUFFER_SIZE 0
#endif /* BSP430_CONSOLE_RX_BUFFER_SIZE */

/** @def BSP430_CONSOLE_TX_BUFFER_SIZE
 *
 * Define this to the size of a buffer to be used for interrupt-driven
 * console output.  The value must not exceed 254, and buffer
 * management is most efficient if the value is a power of 2.
 *
 * If this has a value of zero, character output is not interrupt
 * driven.  cputchar_ni() will block until the UART is ready to accept
 * a new character.
 *
 * @warning By enabling interrupt-driven output the console output
 * routines are no longer safe to call from within interrupt handlers.
 * They may be called with interrupts disabled, but are entitled to
 * enable interrupts in order to drain the transmission buffer to the
 * point where they can complete their output.  Use
 * iBSP430consoleTransmitUseInterrupts_ni() to enable and disable
 * interrupt-driven transmission at runtime.
 *
 * @defaulted */
#ifndef BSP430_CONSOLE_TX_BUFFER_SIZE
#define BSP430_CONSOLE_TX_BUFFER_SIZE 0
#endif /* BSP430_CONSOLE_TX_BUFFER_SIZE */

/** Return a character that was input to the console.
 *
 * @return the next character that was input to the console, or -1 if
 * no characters are available.
 *
 * @note This function is available even if
 * #BSP430_CONSOLE_RX_BUFFER_SIZE is zero.
 */
int cgetchar_ni (void);

/** Return character disregarding interrupt state.
 *
 * This is a wrapper around cgetchar_ni(). */
static int
BSP430_CORE_INLINE
cgetchar (void)
{
  int rv;
  BSP430_CORE_INTERRUPT_STATE_T istate;
  BSP430_CORE_SAVE_INTERRUPT_STATE(istate);
  BSP430_CORE_DISABLE_INTERRUPT();
  rv = cgetchar_ni();
  BSP430_CORE_RESTORE_INTERRUPT_STATE(istate);
  return rv;
}

/** Peek at the next character input to the console
 *
 * Use this to determine whether there's any data ready to be read,
 * without actually consuming it yet.
 *
 * @return the value that would be returned by invoking cgetchar_ni(),
 * but without consuming any pending input.
 *
 * @warning This function is not available if
 * #BSP430_CONSOLE_RX_BUFFER_SIZE is zero.
 *
 * @dependency #BSP430_CONSOLE_RX_BUFFER_SIZE */
int cpeekchar_ni (void);

/** Callback for alarm events.
 *
 * This function will be invoked by the console infrastructure in an
 * interrupt context after received characters have been buffered.
 *
 * @return As with iBSP430halISRCallbackVoid(). */
typedef int (* iBSP430consoleRxCallback_ni) (void);

/** Register a callback for console RX events.
 *
 * If a non-null callback is registered with the console, it will be
 * invoked after each character received on the console is stored in
 * the receive buffer.  The return value of the callback influences
 * how the console RX interrupt handler manages LPM wakeup and other
 * behavior; see @ref callback_retval.
 * 
 * If no callback is registered, the infrastructure will act as though
 * a registered callback did nothing but return
 * #BSP430_HAL_ISR_CALLBACK_EXIT_LPM.
 *
 * @note The infrastructure will add
 * #BSP430_HAL_ISR_CALLBACK_BREAK_CHAIN to any value returned by this
 * callback, including the value returned by a null (default)
 * callback.
 *
 * @warning This function is not available if
 * #BSP430_CONSOLE_RX_BUFFER_SIZE is zero.
 *
 * @param cb the callback to be invoked on received characters, or a
 * null pointer to cause the application to wake from LPM when
 * characters are received.
 *
 * @dependency #BSP430_CONSOLE_RX_BUFFER_SIZE
 */
void vBSP430consoleSetRxCallback_ni (iBSP430consoleRxCallback_ni cb);

/** @def configBSP430_CONSOLE_PROVIDES_PUTCHAR
 *
 * If defined to a true value, the individual character display
 * function used internally to the console module will be made public
 * with the name @c putchar so that it will be used by @c printf(3)
 * when the C library depends on an external @c putchar.
 *
 * The "atomic" behavior promised by #cprintf is not guaranteed for @c
 * printf, @c puts, or any other library function that might invoke
 * this putchar implementation.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_CONSOLE_PROVIDES_PUTCHAR
#define configBSP430_CONSOLE_PROVIDES_PUTCHAR 0
#endif /* configBSP430_CONSOLE_PROVIDES_PUTCHAR */

/** @def configBSP430_CONSOLE_USE_ONLCR
 *
 * If defined to true, the console display routines will always emit a
 * carriage return before a newline.  This provides compatibility with
 * standard terminal programs like minicom.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_CONSOLE_USE_ONLCR
#define configBSP430_CONSOLE_USE_ONLCR 1
#endif /* configBSP430_CONSOLE_USE_ONLCR */

/** @def configBSP430_CONSOLE_LIBC_HAS_VUPRINTF
 *
 * Define to false if your libc does not provide vuprintf.
 * msp430-libc does provide this, and it is used to implement
 * cprintf.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_CONSOLE_LIBC_HAS_VUPRINTF
#define configBSP430_CONSOLE_LIBC_HAS_VUPRINTF 1
#endif /* configBSP430_CONSOLE_LIBC_HAS_VUPRINTF */

/** @def configBSP430_CONSOLE_LIBC_HAS_ITOA
 *
 * Define to false if your libc does not provide itoa.  msp430-libc
 * does provide this, and it is used to implement cputi.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_CONSOLE_LIBC_HAS_ITOA
#define configBSP430_CONSOLE_LIBC_HAS_ITOA 1
#endif /* configBSP430_CONSOLE_LIBC_HAS_ITOA */

/** @def configBSP430_CONSOLE_LIBC_HAS_UTOA
 *
 * Define to false if your libc does not provide utoa.  msp430-libc
 * does provide this, and it is used to implement cputu.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_CONSOLE_LIBC_HAS_UTOA
#define configBSP430_CONSOLE_LIBC_HAS_UTOA 1
#endif /* configBSP430_CONSOLE_LIBC_HAS_UTOA */

/** @def configBSP430_CONSOLE_LIBC_HAS_LTOA
 *
 * Define to false if your libc does not provide ltoa.  msp430-libc
 * does provide this, and it is used to implement cputl.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_CONSOLE_LIBC_HAS_LTOA
#define configBSP430_CONSOLE_LIBC_HAS_LTOA 1
#endif /* configBSP430_CONSOLE_LIBC_HAS_LTOA */

/** @def configBSP430_CONSOLE_LIBC_HAS_ULTOA
 *
 * Define to false if your libc does not provide ultoa.  msp430-libc
 * does provide this, and it is used to implement cputul.
 *
 * @cppflag
 * @defaulted */
#ifndef configBSP430_CONSOLE_LIBC_HAS_ULTOA
#define configBSP430_CONSOLE_LIBC_HAS_ULTOA 1
#endif /* configBSP430_CONSOLE_LIBC_HAS_ULTOA */

/** Like printf(3), but to the console UART.
 *
 * Interrupts are disabled during the duration of the invocation.  On
 * exit, interruptibility state is restored (if entered with
 * interrupts disabled, they remain disabled).
 *
 * If xBSP430consoleInitialize() has not assigned a UART device, the
 * call is a no-op.
 *
 * @param format A printf(3) format string
 *
 * @return Number of characters printed if the console is enabled; 0
 * if it is disabled; a negative error code if an error is
 * encountered
 *
 * @dependency #BSP430_CONSOLE, #configBSP430_CONSOLE_LIBC_HAS_VUPRINTF */
int cprintf (const char * format, ...)
#if __GNUC__ - 0
__attribute__((__format__(printf, 1, 2)))
#endif /* __GNUC__ */
;

/** Like vprintf(3), but to the console UART.
 *
 * @param format A printf(3) format string
 * @param ap A stdarg reference to variable arguments to a calling function.
 * @return as with cprintf(). */
int vcprintf (const char * format, va_list ap);

/** Like puts(3) to the console UART
 *
 * As with #cprintf, interrupts are disabled for the duration of the
 * invocation.
 *
 * @note Any errors returned by the underlying UART implementation
 * while writing are ignored.
 *
 * @param s a string to be emitted to the console
 *
 * @return the number of characters written, including the newline
 */
int cputs (const char * s);

/** Like putchar(3) to the console UART, with interrupts already disabled
 *
 * @param c character to be output
 *
 * @return the character that was output */
int cputchar_ni (int c);

/** Like putchar(3) to the console UART
 *
 * This wraps cputchar_ni() with code to preserve the interrupt enable
 * state.
 *
 * @param c character to be output
 *
 * @return the character that was output */
static int
BSP430_CORE_INLINE
cputchar (int c)
{
  int rv;
  BSP430_CORE_INTERRUPT_STATE_T istate;
  BSP430_CORE_SAVE_INTERRUPT_STATE(istate);
  BSP430_CORE_DISABLE_INTERRUPT();
  rv = cputchar_ni(c);
  BSP430_CORE_RESTORE_INTERRUPT_STATE(istate);
  return rv;
}

/** Like puts(3) to the console UART without trailing newline
 *
 * @note Any errors returned by the underlying UART implementation
 * while writing are ignored.
 *
 * @param s a NUL-terminated string to be emitted to the console
 *
 * @return the number of characters written
 */
int cputtext_ni (const char * s);

/** Like puts(3) to the console UART without trailing newline
 *
 * As with #cprintf, interrupts are disabled for the duration of the
 * invocation.
 *
 * @note Any errors returned by the underlying UART implementation
 * while writing are ignored.
 *
 * @param s a NUL-terminated string to be emitted to the console
 *
 * @return the number of characters written
 */
int cputtext (const char * s);

/** Like puts(3) to the console UART without trailing newline and
 * with explicit length instead of a terminating NUL.
 *
 * @note Any errors returned by the underlying UART implementation
 * while writing are ignored.
 *
 * @param cp first of a series of characters to be emitted to the
 * console
 *
 * @param len number of characters to emit
 *
 * @return the number of characters written
 */
int cputchars_ni (const char * cp, size_t len);

/** Like puts(3) to the console UART without trailing newline and
 * with explicit length instead of a terminating NUL.
 *
 * As with #cprintf, interrupts are disabled for the duration of the
 * invocation.
 *
 * @note Any errors returned by the underlying UART implementation
 * while writing are ignored.
 *
 * @param cp first of a series of characters to be emitted to the
 * console
 *
 * @param len number of characters to emit
 *
 * @return the number of characters written
 */
int cputchars (const char * cp, size_t len);

/** Format an int using itoa and emit it to the console.
 *
 * @param n the integer value to be formatted
 * @param radix the radix to use when formatting
 *
 * @warning The implementation assumes that @p radix is at least 10.
 * Passing a smaller radix will likely result in stack corruption.
 *
 * @return the number of characters emitted
 *
 * @dependency #BSP430_CONSOLE, #configBSP430_CONSOLE_LIBC_HAS_ITOA */
int cputi_ni (int n, int radix);

/** Format an int using utoa and emit it to the console.
 *
 * @param n the integer value to be formatted
 * @param radix the radix to use when formatting
 *
 * @warning The implementation assumes that the radix is at least 10.
 * Passing a smaller radix will likely result in stack corruption.
 *
 * @return the number of characters emitted
 *
 * @dependency #BSP430_CONSOLE, #configBSP430_CONSOLE_LIBC_HAS_UTOA */
int cputu_ni (unsigned int n, int radix);

/** Format an int using ltoa and emit it to the console.
 *
 * @param n the integer value to be formatted
 * @param radix the radix to use when formatting
 *
 * @warning The implementation assumes that the radix is at least 10.
 * Passing a smaller radix will likely result in stack corruption.
 *
 * @return the number of characters emitted
 *
 * @dependency #BSP430_CONSOLE, #configBSP430_CONSOLE_LIBC_HAS_LTOA */
int cputl_ni (long n, int radix);

/** Format an int using itoa and emit it to the console.
 *
 * @param n the integer value to be formatted
 * @param radix the radix to use when formatting
 *
 * @warning The implementation assumes that the radix is at least 10.
 * Passing a smaller radix will likely result in stack corruption.
 *
 * @return the number of characters emitted
 *
 * @dependency #BSP430_CONSOLE, #configBSP430_CONSOLE_LIBC_HAS_ULTOA */
int cputul_ni (unsigned long n, int radix);

/** Initialize and return the console serial HAL instance.
 *
 * This configures the platform-specified serial HAL instance
 * identified by #BSP430_CONSOLE_SERIAL_PERIPH_HANDLE as specified by
 * #BSP430_CONSOLE_BAUD_RATE.  If #BSP430_PLATFORM_SPIN_FOR_JUMPER is
 * true, it will invoke vBSP430platformSpinForJumper_ni().  Once the
 * console is configured and any required delays completed it will
 * return, allowing use of cprintf() and related functions.
 *
 * If this function is invoked multiple times without an intervening
 * call to iBSP430consoleDeconfigure(), the existing configuration is
 * unchanged.
 *
 * @return 0 if the console was successfully initialized, -1 if an
 * error occurred. */
int iBSP430consoleInitialize (void);

/** Deconfigure the console serial HAL instance
 *
 * This routine closes the HAL serial instance, decoupling it from any
 * callbacks and turning it off.  The instance may be re-enabled by
 * re-invoking iBSP430consoleInitialize().
 *
 * You might need this function if you change the rate of the clock on
 * which the console baud generator depends.
 *
 * @return 0 if the deconfiguration was successful, -1 if an error
 * occurred. */
int iBSP430consoleDeconfigure (void);

/** Return a reference to the console device.
 *
 * @return the serial HAL instance used for console interaction.  A
 * null pointer is returned if the console has not been successfully
 * initialized. */
hBSP430halSERIAL hBSP430console (void);

/** Control whether console output uses interrupt-driven transmission.
 *
 * When #BSP430_CONSOLE_TX_BUFFER_SIZE is configured to a positive
 * value, it is normally improper to use the console output routines
 * from within interrupt handlers and in other cases where interrupts
 * are disabled, since the routines might enable interrupts to allow
 * the transmission buffer to drain.  This routine can be used at
 * runtime to disable the interrupt-based transmission, thus allowing
 * use of direct, busy-waiting console output.
 *
 * @note You probably want to invoke vBSP430consoleFlush() prior to
 * disabling interrupt-driven transmission.  If you don't, whatever
 * was unflushed will be displayed once the transmission is
 * re-enabled.
 *
 * @param enablep nonzero if interrupt-drive transmission is to be
 * used; zero to disable the transmit interrupt on the console UART
 * and use direct UART writes instead.
 *
 * @return 0 if the configuration was accepted.  -1 if @p enable is
 * nonzero but the application was not configured with
 * interrupt-driven transmission enabled.
 */
int iBSP430consoleTransmitUseInterrupts_ni (int enablep);

/** Potentially block until space is available in console transmit buffer.
 *
 * This function causes the caller to block until the interrupt-driven
 * console transmit buffer has drained to the point where at least @p
 * want_available bytes are available.
 *
 * If the console does not use interrupt-driven transmission, this
 * function immediately returns zero.
 *
 * @note The return value of this function indicates whether it was
 * necessary to enable interrupts in order to achieve the desired
 * available space.  In such a case an application may need to
 * re-check other conditions to ensure there is no pending work prior
 * to entering low power mode.
 *
 * @param want_available the number of bytes that are requested.  A
 * negative number requires that the transmit buffer be empty (i.e.,
 * flushed).
 *
 * @return
 * @li Zero if @p want_available bytes were available on entry without
 * suspending;
 * @li A positive number if the bytes are now available, but the
 * function had to suspend (enabling interrupts) in order to obtain
 * that space;
 * @li -1 if @p want_available is larger than
 * #BSP430_CONSOLE_TX_BUFFER_SIZE-1, which is the maximum number of
 * bytes that can be made available. */
int iBSP430consoleWaitForTxSpace_ni (int want_available);

/** Flush any pending data in the console transmit buffer.
 *
 * The caller may enter low power mode while waiting for the console
 * transmission infrastructure to drain the buffer.  On return, all
 * queued output will have been transmitted.
 *
 * If the console does not use interrupt driven transmission, this
 * function will simply spin until the last character has been
 * transmitted by the UART.
 *
 * @return 0 if the console was flushed without suspending; a positive
 * number of the application had to suspend to permit interrupt-driven
 * transmission to complete.
 */
int iBSP430consoleFlush (void);

#endif /* BSP430_UTILITY_CONSOLE_H */
