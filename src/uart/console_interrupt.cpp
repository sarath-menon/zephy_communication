#include <console/console.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/printk.h>
#include <zephyr.h>

static int test_fifo_read(void) {
  const struct device *uart_dev = device_get_binding(UART_DEVICE_NAME);

  /* Verify uart_irq_callback_set() */
  uart_irq_callback_set(uart_dev, uart_fifo_callback);

  /* Enable Tx/Rx interrupt before using fifo */
  /* Verify uart_irq_rx_enable() */
  uart_irq_rx_enable(uart_dev);

  TC_PRINT("Please send characters to serial console\n");

  data_received = false;
  while (data_received == false) {
  }

  /* Verify uart_irq_rx_disable() */
  uart_irq_rx_disable(uart_dev);

  return TC_PASS;