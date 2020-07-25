#include <stdio.h>
#include "ets_sys.h"
#include "user_interface.h"
#include "ets_sys.h"

#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

#define LED BIT2

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
static os_timer_t ledTimer;
void ICACHE_FLASH_ATTR ledTimer_cb(void *arg) {
    static int ledStatus = 0;
    if (!ledStatus) {
        gpio_output_set(LED, 0, LED, 0);
        ledStatus = 1;
    } else {
        gpio_output_set(0, LED, LED, 0);
        ledStatus = 0;
    }
}
void ICACHE_FLASH_ATTR sdk_init_done_cb(void) {
    os_timer_setfn(&ledTimer, (os_timer_func_t *)ledTimer_cb, NULL);
    os_timer_arm(&ledTimer, 500 , 1);
}
void ICACHE_FLASH_ATTR user_init() {
    gpio_init();
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
    system_init_done_cb(sdk_init_done_cb);
}