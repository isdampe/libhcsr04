#include <unistd.h>
#include <sys/time.h>
#include "hcsr04.h"

hcsr04 hcsr04_create(void (*trigger_pin)(uint8_t), uint8_t (*read_echo_pin)())
{
	hcsr04 instance;

	instance.trigger_pin = trigger_pin;
	instance.read_echo_pin = read_echo_pin;

	return instance;
}

void hcsr04_trigger(hcsr04 *instance)
{
	instance->trigger_pin(0x1);
	usleep(HCSR04_PULSE_TIMER_uS);
	instance->trigger_pin(0x0);
}

double hcsr04_read(hcsr04 *instance)
{
	struct timeval t1, t2;
	uint8_t buf = 0;
	double diff;

	//Trigger the board.
	hcsr04_trigger(instance);
	gettimeofday(&t1, NULL);

	//Read echo burst.
	while (buf == 0)
		buf = instance->read_echo_pin();

	gettimeofday(&t2, NULL);
	diff = t2.tv_usec - t1.tv_usec;

	return (diff / HCSR04_DISTANCE_DENOMINATOR_CM) * 10;

}
