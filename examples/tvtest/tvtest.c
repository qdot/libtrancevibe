/***
 * @file tvtest.c
 * @brief Trancevibe test utility
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2005-2010 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 * Project info at http://libtrancevibe.nonpolynomial.com/
 *
 */

#include "trancevibe.h"
#ifndef WIN32
#include "unistd.h"
#elif WIN32
#include "windows.h"
#endif
#include <stdio.h>

int main(int argc, char** argv)
{
	int device_count;
	int i;
	int ret = 0;
	trancevibe* tv = trancevibe_create();
	trancevibe_init(tv);
	device_count = trancevibe_get_count(tv);
	if(device_count < 0)
	{
		printf("Error getting device count: %d\n", device_count);
		return -1;
	}
	printf("Devices Connected: %d\n", device_count);
	for(i = 0; i < device_count; ++i)
	{
		if(trancevibe_open(tv, i) < 0)
		{
			printf("Cannot open device %d\n", i);
			ret = -1;
			break;
		}
		printf("Opened device %d\n", i);

		if(trancevibe_set_speed(tv, 0xff, 10) < 0)
		{
			printf("Cannot write to device\n");
		}
		
#ifndef WIN32
		sleep(1);
#elif WIN32
		Sleep(1000);
#endif
		if(trancevibe_set_speed(tv, 0x0, 10) < 0)
		{
			printf("Cannot write to device\n");
		}
		trancevibe_close(tv);

	}
	trancevibe_delete(tv);
	return ret;
}
