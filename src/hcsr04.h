#ifndef HCSR04_H
#define HCSR04_H 1
#include <stdint.h>

#define HCSR04_ECHO_TIMEOUT_CLOCKS 600
#define HCSR04_PULSE_TIMER_uS 0xA
#define HCSR04_DISTANCE_DENOMINATOR_CM 0x3A

typedef struct
{
	void (*trigger_pin)(uint8_t);
	uint8_t (*read_echo_pin)();
} hcsr04;

/**
 * Creates a new hcsr04 instance.
 * @param	void (*trigger_pin)(uint8_t)	Pointer to function that sets the trigger pin on the HCSR04.
 * @param	uint8_t (*read_echo_pin)()		Pointer to function that reads HIGH / LOW of echo pin on the HCSR04.
 * @return	hcsr04							The hcsr04 instance.
 */
hcsr04 hcsr04_create(void (*trigger_pin)(uint8_t), uint8_t (*read_echo_pin)());

/**
 * Sends the trigger event signal to the hcsr04.
 * @param	hcsr04 *instance	The hcsr04 instance pointer.
 * @return	void
 */
void hcsr04_trigger(hcsr04 *instance);

/**
 * Reads the estimated distance in mm from the hcsr04.
 * @param	hcsr04 *instance	The hcsr04 instance pointer.
 * @return	double				The estimated distance in millimetres, or -1 if a timeout occured.
 */
double hcsr04_read(hcsr04 *instance);

#endif
