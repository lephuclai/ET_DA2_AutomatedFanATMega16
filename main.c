//#define F_CPU 1000000UL
#include <avr/io.h>
//#include <util/delay.h>
#include "pwm.h"
#include "dcmotor.h"
#include "gpio.h"
#include "common_macros.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "lcd.h"

// Typedef for the fan state
typedef enum
{
	OFF,ON
}FANSTATE;

int main(void){
	uint8 temperature=0;
	FANSTATE fanState;

	/* Create configuration structure for ADC driver */
	ADC_configPtr ADC_Config = {INTERNAL, ADLAR_RIGHT, ENABLE, FCPU_8, POLLING, AUTOTRIGGER_DISABLE, FREE_RUNNING};

	LCD_init(); /* initialize LCD driver */

	ADC_init(&ADC_Config); /* initialize ADC driver */

	DCMOTOR_init(); /* initialize DC Motor driver */

	/* display on LCD */
	LCD_displayStringRowColumn(0, 4,"Fan is ");
	LCD_displayStringRowColumn(1,4,"Temp=     C ");
	while(1){
		// Get the sensor temperature reading
		temperature = LM35_getTemperature();

		/* Display fan ON or OFF */
		if ( fanState == ON)
		{
			LCD_displayStringRowColumn(0, 11, "ON");
		}
		else if ( fanState == OFF)
		{
			LCD_displayStringRowColumn(0, 11, "OFF");
		}

		/* Rotate/Stop motor based on temperature value */
		if(temperature<10){
			fanState = OFF;
			DCMOTOR_rotate(STOP, 0);
		}else{
			fanState = ON;
			LCD_displayCharacter(' ');  /* To prevent "ONF" to be displayed when switching from OFF to ON */
			if(temperature>=10 && temperature < 30){
				// Rotate motor 25% speed
				DCMOTOR_rotate(CLOCKWISE, 25);
			}else if(temperature>=30 && temperature < 60){
				 // Rotate motor 50% speed
				DCMOTOR_rotate(CLOCKWISE, 50);
			}else if(temperature>=60 && temperature < 120){
				// Rotate motor 75% speed
				DCMOTOR_rotate(CLOCKWISE, 75);
			}else if(temperature>=120){
				// Rotate motor 100% speed
				DCMOTOR_rotate(CLOCKWISE, 100);
			}
		}

		/* Display temperature value */
		LCD_moveCursor(1,11);
		if(temperature >= 100)
		{
			LCD_integerToString(temperature);
			//_delay_us(1000000);
		}
		else
		{
			LCD_integerToString(temperature);
			LCD_displayCharacter(' '); // If temperature is less than 3 digits
			//_delay_us(1000000);
		}
	}
}
