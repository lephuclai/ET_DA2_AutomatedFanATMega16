#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LM35_SENSOR_CHANNEL			ADC2
#define SENSOR_MAX_TEMPERATURE		150
#define SENSOR_MAX_VOLTAGE			1.5

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */

uint8 LM35_getTemperature(void);

#endif
