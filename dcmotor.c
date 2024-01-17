#include "dcmotor.h"
#include "avr/io.h"
#include "gpio.h"
#include "pwm.h"
#include "common_macros.h"

/*
 * Description :
 * Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DCMOTOR_init(void){
	// Set motor pins as output pins
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN2, PIN_OUTPUT);

	// Stop the motor initially
	GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN1,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN2 ,LOGIC_LOW);
}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DCMOTOR_rotate(DCMOTOR_STATE state,uint8 speed){
	// Start PWM timer to control the fan speed according to the given value
	PWM_Timer0_Start(speed);
	if(state == STOP){
		// Stop the motor
		GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN2 ,LOGIC_LOW);
	}else if(state == CLOCKWISE){
		// Rotate Clockwise
		GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN1,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN2 ,LOGIC_LOW);
	}else if(state == ANTICLOCKWISE){
		// Rotate Anti-clockwise
		GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN2 ,LOGIC_HIGH);
	}
}




