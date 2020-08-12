//
// Created by data-scientist on 11.08.2020.
//

#ifndef HIGH_LEVEL_ESP8266_UART_H
#define HIGH_LEVEL_ESP8266_UART_H

#include "driver/uart.h"
#include "ets_sys.h"
#include "c_types.h"
#include "eagle_soc.h"

uint8 fifo_len;
uint8_t fl;

void uart0_rx_intr_handler(void *para);
void init_uart(void);

//missing definitions
void ets_isr_mask(unsigned intr);
void ets_isr_unmask(unsigned intr);
#endif //HIGH_LEVEL_ESP8266_UART_H