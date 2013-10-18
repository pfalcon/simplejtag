#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>

#include "simplejtag_proto.h"
#include HW_CONFIG

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();
    tck::port::enable();
    tms::port::enable();
    tck::output();
    tms::output();
    tck::low();
    tms::low();
#ifdef USE_JTAG
    tdi::port::enable();
    tdo::port::enable();
    tdi::output();
    tdo::input();
    tdi::low();
#endif
#ifdef USE_LED
    led::port::enable();
    led::output();
    led::low();
#endif

    while (true) {
        uint8_t b = uart::read();
        uint8_t resp = RESP_ACK;
        switch(b) {
#ifdef USE_LED
        case CMD_BLINK_ON:
            led::high();
            break;
        case CMD_BLINK_OFF:
            led::low();
            break;
#endif
#ifdef USE_SWD
        case CMD_WRITE_TMS:
        case CMD_WRITE_TMS + 1:
            tms::output();
            tms::set(b & 1);
            break;
        case CMD_WRITE_TCK:
        case CMD_WRITE_TCK + 1:
            tck::set(b & 1);
            break;
        case CMD_READ_TMS:
            tms::input();
            resp = RESP_VAL + (bool)tms::value();
            break;
#endif
#ifdef USE_JTAG
        case CMD_READ_TDO:
            resp = RESP_VAL + (bool)tdo::value();
            break;
        default:
            if ((b & ~0x07) == CMD_WRITE_TCK_TMS_TDI) {
                tms::output();
                tck::set((b & 0x04));
                tms::set((b & 0x02));
                tdi::set((b & 0x01));
            } else {
                resp = RESP_NACK;
            }
#endif
        }

        uart::write(resp);
    }
}
