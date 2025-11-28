#include <avr/io.h>
#include <avr/interrupt.h>
#include "d_led.h"

int main(void) {
  d_led_init();
  cy1 = 1;
  cy2 = 2;
  cy3 = 3;
  sei();

  while (1) {

  }
}
