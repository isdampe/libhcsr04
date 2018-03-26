#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "hcsr04.h"

static pthread_mutex_t hcsr04_mutex = PTHREAD_MUTEX_INITIALIZER;

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
	struct timespec t1, t2;
	unsigned long long mc = 0;
	uint8_t buf = 0;
	double diff;

	pthread_mutex_lock(&hcsr04_mutex);

	//Trigger the board.
	hcsr04_trigger(instance);
	clock_gettime(CLOCK_REALTIME, &t1);

	//Read echo burst.
	for (mc=0; buf == 0 && mc < HCSR04_ECHO_TIMEOUT_CLOCKS; ++mc)
	{
		buf = instance->read_echo_pin();
		usleep(100);
	}

	clock_gettime(CLOCK_REALTIME, &t2);
	diff = t2.tv_nsec - t1.tv_nsec;

	pthread_mutex_unlock(&hcsr04_mutex);

	if (mc >= HCSR04_ECHO_TIMEOUT_CLOCKS)
		return -1;

	return (diff / HCSR04_DISTANCE_DENOMINATOR_CM) / 100;

}
