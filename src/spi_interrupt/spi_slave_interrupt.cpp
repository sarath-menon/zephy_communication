#include <device.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <stdio.h>

#define MY_DEV_IRQ 24 /* device uses IRQ 24 */
#define MY_DEV_PRIO 2 /* device uses interrupt priority 2 */
// #define MY_ISR_ARG DEVICE_GET("GPIOA")

static struct gpio_callback btn_gpioa_cb;

// GPIO callback
void _on_button(struct device *gpio, struct gpio_callback *cb, uint32_t pins) {
  printk("p %p cb %p pins %08x\n", gpio, cb, pins);
}

void _init_buttons(void) {
  const struct device *gpioa = device_get_binding("GPIOA");

  gpio_pin_configure(gpioa, 10,
                     (GPIO_INPUT | GPIO_INT_EDGE_RISING | GPIO_PULL_DOWN));

  gpio_init_callback(&btn_gpioa_cb, _on_button, BIT(10));

  if (gpio_add_callback(gpioa, &btn_gpioa_cb) < 0) {
    printk("btn cb failed %s", "GPIOA");
    return;
  }

  // if (gpio_add_callback(gpioa, &btn_gpioa_cb) < 0) {
  //   printk("btn cb failed %s", "GPIOA");
  //   return;
  // }

  // if (gpio_add_callback(gpiob, &btn_gpiob_cb) < 0) {
  //   printk("btn cb failed %s", "GPIOB");
  //   return;
  // }

  // gpio_pin_enable_callback(gpioa, 10);
  // gpio_pin_enable_callback(gpiob, 4);
  // gpio_pin_enable_callback(gpiob, 5);
}

void main() {
  const struct device *gpio = device_get_binding("GPIOA");

  while (1) {
  }
}
