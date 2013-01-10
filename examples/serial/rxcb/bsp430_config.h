/* Use a crystal if one is installed.  Much more accurate timing
 * results. */
#define BSP430_PLATFORM_BOOT_CONFIGURE_LFXT1 1

/* Application does output: support spin-for-jumper */
#define configBSP430_PLATFORM_SPIN_FOR_JUMPER 1

/* Support console output, with RX and TX buffers */
#define configBSP430_CONSOLE 1
#define BSP430_CONSOLE_RX_BUFFER_SIZE 8
#define BSP430_CONSOLE_TX_BUFFER_SIZE 32

/* Monitor uptime and provide generic ACLK-driven timer and delay */
#define configBSP430_UPTIME 1
#define configBSP430_UPTIME_DELAY 1

/* Get platform defaults */
#include <bsp430/platform/bsp430_config.h>
