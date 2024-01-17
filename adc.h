 #ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*
 * Description :
 * Select the way VREF is selected
 * 1.AREF : VREF is entered throw and external AREF PIN in micro-controller.
 * 2.AVCC : VREF is the same as AVCC (5v analog).
 * 3.INTERNAL : VREF is 2.56v from internal micro-controller circuit.
 * Done using ADMUX Register.
 */
typedef enum{
	AREF=0x00 , AVCC=0x40 , INTERNAL=0xC0
}ADC_VREF_SEL;

/*
 * Description :
 * Adjust ADC DATA Register right/left in the ADLAR pin using ADMUX Register.
 */
typedef enum{
	ADLAR_RIGHT=0x00, ADLAR_LEFT=0x20
}ADC_ADLAR_SEL;

/*
 * Description :
 * Select ADC channel to convert it to digital according to channel number in the MUX4:0 Bits with ADMUX Register.
 */
typedef enum{
	ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7
}ADC_MUX_SEL;

/*
 * Description :
 * Enable/Disable ADC using ADCSRA Register.
 */
typedef enum{
	DISABLE,ENABLE=0x80
}ADC_ENABLE;

/*
 * Description :
 * Select ADC clock F_ADC=F_CPU/Prescaler with ADCSRA Register.
 */
typedef enum{
	FCPU_2=0x00, FCPU_4=0x02,FCPU_8=0x03,FCPU_16=0x04,FCPU_32=0x05,FCPU_64=0x06,FCPU_128=0x07
}ADC_PRESCALAR_SEL;

/*
 * Description :
 * Select ADC channel to work using polling/interrupt mode with ADCSRA Register.
 */
typedef enum{
	POLLING = 0x00, INT_ENABLED = 0x08
}ADC_MODE;

/*
 * Description :
 * Enable/Disable auto-trigger mode using ADATE bit in ADCSRA register
 */
typedef enum{
	AUTOTRIGGER_DISABLE, AUTOTRIGGER_ENABLE = 0x20
}ADC_AUTOTRIGGER_ENABLE;

/*
 * Description :
 * Select ADC Auto-Trigger source to of ADC in SFIOR Register.
 */
typedef enum{
	FREE_RUNNING, ANALOG_COMPARATOR=0x20, EXTERNAL_INT0=0x40, TIMER0_CMP=0x60, TIMER0_OF=0x80, TIMER1B_CMP=0xA0, TIMER1_OF=0xC0, TIMER1_CAPTURE=0xE0
}ADC_AUTOTRIGGER_SOURCE;

/*
 * Description :
 * Structure variable passed to ADC_init function as parameter in order to make the ADC_init function configurable
 */
typedef struct{
ADC_VREF_SEL vref;
ADC_ADLAR_SEL adlar;
ADC_ENABLE enable;
ADC_PRESCALAR_SEL prescalar;
ADC_MODE mode;
ADC_AUTOTRIGGER_ENABLE autotriggerEnable;
ADC_AUTOTRIGGER_SOURCE autotriggerSource;
}ADC_configPtr;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function that takes adc config pointer and initialize the adc as needed
 * You can configure your adc init by passing the ADC_configPtr to the function
 */
void ADC_init(const ADC_configPtr* configPtr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel using polling
 * and returns the digital data after conversion.
 */
uint16 ADC_readChannel(ADC_MUX_SEL channelNum);
#endif
