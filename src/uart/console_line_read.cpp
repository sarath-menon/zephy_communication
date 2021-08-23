#include <console/console.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/printk.h>
#include <zephyr.h>

void main(void) {
  console_getline_init();

  printk("Enter a line\n");

  while (1) {
    char *s = console_getline();

    printk("line: %s\n", s);
    printf("Thrust command: %f\n", atof(s));
    printk("last char was: 0x%x\n", s[strlen(s) - 1]);
  }
}