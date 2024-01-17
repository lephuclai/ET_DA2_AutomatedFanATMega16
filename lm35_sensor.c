#define F_CPU 1000000UL
#include <util/delay.h>
#include "lm35_sensor.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "adc.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void){
	uint8 temperature;
	// Read the channel which sensor is connected to
	uint16 adcValue = ADC_readChannel(LM35_SENSOR_CHANNEL);
	// Calculate the temperature using the following formula
	temperature = (uint8)(((uint32)adcValue*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLTAGE));
	_delay_ms(1000);
	return temperature;
}
