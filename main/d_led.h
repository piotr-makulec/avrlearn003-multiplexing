#ifndef _d_led_h
#define _d_led_h

#define LED_DATA PORTD
#define LED_DATA_DIR DDRD
#define ANODES_PORT PORTB
#define ANODES_DIR DDRB

#define CB0 (1<<PB0)
#define CB1 (1<<PB1)
#define CB2 (1<<PB2)

#define SEG_A (1<<0)
#define SEG_B (1<<1)
#define SEG_C (1<<2)
#define SEG_D (1<<3)
#define SEG_E (1<<4)
#define SEG_F (1<<5)
#define SEG_G (1<<6)
#define SEG_H (1<<7)

extern volatile uint8_t cy1;
extern volatile uint8_t cy2;
extern volatile uint8_t cy3;

void d_led_init(void);

#endif
