#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	STOP, CLOCKWISE, ANTICLOCKWISE
}DCMOTOR_STATE;

/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID            PORTB_ID

#define DC_MOTOR_PIN_IN1            PIN0_ID
#define DC_MOTOR_PIN_IN2            PIN1_ID
#define DC_MOTOR_PIN_IN3
#define DC_MOTOR_PIN_IN4

#define DC_MOTOR_PIN_EN1            PIN3_ID
#define DC_MOTOR_PIN_EN2

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DCMOTOR_init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DCMOTOR_rotate(DCMOTOR_STATE state,uint8 speed);
#endif
