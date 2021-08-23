#include <device.h>
#include <drivers/uart.h>
#include <soc.h>
#include <stdio.h>
#include <string.h>

static const char *poll_data = "This is a POLL test.\r\n";

void main() {
  // Data to be exchanged
  unsigned char test_char = '8';

  // UART 2 is reserved for the serial console
  const struct device *uart = device_get_binding("UART_2");

  // Initialize UART 1 [Pin 9:Tx, Pin 10: Rx]
  // const struct device *uart = device_get_binding("UART_1");

  while (1) {

    // uart_poll_out(uart, test_char);
    for (int i = 0; i < strlen(poll_data); i++) {
      uart_poll_out(uart, poll_data[i]);
    }
    // int status = uart_tx(uart, data, sizeof(data), 1000);
    // printf("Sent: %d\n", status);

    k_sleep(K_TIMEOUT_ABS_MS(250));
  }
}
