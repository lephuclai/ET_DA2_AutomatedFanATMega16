#include "adc.h"
#include "avr/io.h" /* To use the ADC Ports Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */


/*
 * Description :
 * Function that takes adc config pointer and initialize the adc as needed
 * You can configure your adc init by passing the ADC_configPtr to the function
 */
void ADC_init(const ADC_configPtr* configPtr){
	ADMUX |= configPtr->vref | configPtr->adlar;
	ADCSRA |= configPtr->enable | configPtr->mode | configPtr->autotriggerEnable | configPtr->prescalar;
	SFIOR |= configPtr->autotriggerSource;
}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel using polling
 * and returns the digital data after conversion.
 */
uint16 ADC_readChannel(ADC_MUX_SEL channelNum){
	// Channel from 0 -> 7 only
	channelNum &= 0x07;
	// Clear first 5 bits for MUX4:0
	ADMUX &= 0xE0;
	// Set channel to read
	ADMUX |= channelNum;
	// Start conversion by setting ADSC bit to 1
	SET_BIT(ADCSRA,ADSC);
	// Use polling wait until flag ADIF is set to 1
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	// Clear the ADIF flag
	SET_BIT(ADCSRA,ADIF);
	return ADC;

}
