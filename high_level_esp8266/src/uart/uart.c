//
// Created by data-scientist on 11.08.2020.
//

#include "../../include/uart/uart.h"

char rx_buf[100] = {};

//------------------------------------------------------
void uart0_rx_intr_handler(void *para)
{
    if (UART_FRM_ERR_INT_ST == (READ_PERI_REG(UART_INT_ST(UART0)) & UART_FRM_ERR_INT_ST)) {
        WRITE_PERI_REG(UART_INT_CLR(UART0), UART_FRM_ERR_INT_CLR);
    }
    if (UART_RXFIFO_FULL_INT_ST == (READ_PERI_REG(UART_INT_ST(UART0)) & UART_RXFIFO_FULL_INT_ST)) {
        uart_rx_intr_disable(UART0);
    } else if (UART_RXFIFO_TOUT_INT_ST == (READ_PERI_REG(UART_INT_ST(UART0)) & UART_RXFIFO_TOUT_INT_ST)) {
        uart_rx_intr_disable(UART0);
    } else if (UART_TXFIFO_EMPTY_INT_ST == (READ_PERI_REG(UART_INT_ST(UART0)) & UART_TXFIFO_EMPTY_INT_ST)) {
        CLEAR_PERI_REG_MASK(UART_INT_ENA(UART0), UART_TXFIFO_EMPTY_INT_ENA);
        WRITE_PERI_REG(UART_INT_CLR(UART0), UART_TXFIFO_EMPTY_INT_CLR);
    } else if (UART_RXFIFO_OVF_INT_ST == (READ_PERI_REG(UART_INT_ST(UART0)) & UART_RXFIFO_OVF_INT_ST)) {
        WRITE_PERI_REG(UART_INT_CLR(UART0), UART_RXFIFO_OVF_INT_CLR);
    }
    fifo_len = (READ_PERI_REG(UART_STATUS(UART0))>>UART_RXFIFO_CNT_S)&UART_RXFIFO_CNT; // method from doc
    if(fifo_len>0) fl=1;
}

void init_uart(void) {
    uart_init(BIT_RATE_115200, BIT_RATE_115200);
    ETS_UART_INTR_DISABLE(); // disable uart interrupt
    ETS_UART_INTR_ATTACH(uart0_rx_intr_handler,  rx_buf);
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_U0TXD_U);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);
    ETS_UART_INTR_ENABLE(); // enable uart interrupt
}