#include <cpu.hpp>
#include <board.hpp>
#include <gpio.hpp>
#include <uart.hpp>

using namespace PTL;

// for bitbang:
//typedef UART<board::freq, 9600, board::pin_uart_tx, board::pin_uart_rx, timer> uart;
typedef UART<1 MHZ, 9600, USCI_A> uart;

// Compatible with mchck-swd
typedef Pin<P1, Bit4> tck; // aka SWDCLK
typedef Pin<P1, Bit5> tms; // aka SWDIO
// Physically adjacent to the ones above
typedef Pin<P2, Bit0> tdi;
typedef Pin<P2, Bit1> tdo;

typedef board::LED led;


// Individual firmware features
#define USE_JTAG
#define USE_SWD
#define USE_LED
