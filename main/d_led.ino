#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "d_led.h"

const uint8_t digits[] PROGMEM = {
  ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F),
  ~(SEG_B | SEG_C),
  ~(SEG_A | SEG_B | SEG_D | SEG_E | SEG_G),
  ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_G),
  ~(SEG_B | SEG_C | SEG_F | SEG_G),
  ~(SEG_A | SEG_C | SEG_D | SEG_F | SEG_G),
  ~(SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G),
  ~(SEG_A | SEG_B | SEG_C | SEG_F),
  ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G),
  ~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)
};

volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;

void d_led_init(void) {
  LED_DATA_DIR = 0xFF;
  LED_DATA = 0xFF;
  ANODES_DIR |= CB0 | CB1 | CB2;
  ANODES_PORT |= CB0 | CB1 | CB2;
  //timer
  TCCR0A |= (1 << WGM01); // CTC mode
  TCCR0B |= (1 << CS02) | (1 << CS00); //prescaler = 1024
  OCR0B = 38; //interrupt at tic 38
  TIMSK0 |= (1 << OCIE0A); //CTC interrupt on
}

// INTERRUPT

ISR(TIMER0_COMPA_vect) {
  static uint8_t counter = 1; //switching the anodes
  ANODES_PORT = (ANODES_PORT & 0xF8) | (~counter & 0x07); //zeroing the anodes

  if (counter == 1) LED_DATA = pgm_read_byte(&digits[cy1]);
  else if (counter == 2) LED_DATA = pgm_read_byte(&digits[cy2]);
  else if (counter == 4) LED_DATA = pgm_read_byte(&digits[cy3]);

  counter <<= 1;
  if (counter > 4)
    counter = 1;
}
