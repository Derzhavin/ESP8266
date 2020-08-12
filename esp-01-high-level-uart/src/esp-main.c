#include <stdio.h>
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"
#include "gpio.h"
#include "driver/uart.h"

#include "uart/uart.h"

//------------------------------------------------------
//------------------------------------------------------
uint32 ICACHE_FLASH_ATTR user_rf_cal_sector_set(void)
{
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 8;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }
    return rf_cal_sec;
}

extern uint8 fifo_len;
extern uint8_t fl;

void ICACHE_FLASH_ATTR user_init()
{
    uint16_t i=0;
    uint8 d_tmp = 0;
    uint8 idx=0;
    init_uart();
    while(1) {
        while (!fl) {
            i++;
            if (i > 500) {
                i = 0;
                system_soft_wdt_feed();
            }
            ets_delay_us(1000);
        }
        fl = 0;
        os_printf("fifo_len: %d\r\n", fifo_len);
        for (idx = 0; idx < fifo_len; idx++) {
            d_tmp = READ_PERI_REG(UART_FIFO(UART0)) & 0xFF;
            if ((d_tmp != 0x0D) && (d_tmp != 0x0A))
                os_printf("%c\n", d_tmp);
        }
        os_printf("\n");

        WRITE_PERI_REG(UART_INT_CLR(UART0), UART_RXFIFO_FULL_INT_CLR | UART_RXFIFO_TOUT_INT_CLR);
        uart_rx_intr_enable(UART0);
    }
}
//------------------------------------------------------