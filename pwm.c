#include "pwm.h"
#include "avr/io.h" /* To use the PWM Ports Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle_percentage){
	// Initially set timer to 0
	TCNT0 = 0;
	// Compare value calculation as the input is a percentage from 0% -> 100%
	OCR0 = ((float)duty_cycle_percentage/100) * 255;
	// Set PB3 as output to use PWM
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
