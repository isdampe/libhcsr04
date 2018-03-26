#include <stdio.h>
#include <unistd.h>
#include "hcsr04.h"

void set_pin(uint8_t status)
{
	printf("Setting pin status: %i\n", status);
}

uint8_t read_pin()
{
	usleep(500);
	return 1;
}

int main()
{
	hcsr04 instance = hcsr04_create(&set_pin, &read_pin);

	double res = hcsr04_read(&instance);
	printf("Distance: %fmm\n", res);

	return 0;
}
