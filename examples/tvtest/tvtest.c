/*
 * Implementation file for Trancevibrator Test Program
 *
 * Copyright (c) 2005-2007 Kyle Machulis/Nonpolynomial Labs <kyle@nonpolynomial.com>  
 *
 * More info on Nonpolynomial Labs @ http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libtrancevibe/
 *
 * This file is covered by the MIT License, read LICENSE.txt for details.
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
	trancevibe tv;
	int device_count;
	int i;
	device_count = trancevibe_get_count();
	printf("Devices: %d\n", device_count);
	for(i = 0; i < device_count; ++i)
	{
		if(trancevibe_open(&tv, i) < 0)
		{
			printf("Cannot open device %d\n", i);
			break;
		}
		printf("Opened device %d\n", i);

		if(trancevibe_set_speed(tv, 0xff, 1) < 0)
		{
			printf("Cannot write to device\n");
		}
#ifndef WIN32
		sleep(1);
#elif WIN32
		Sleep(1000);
#endif
		if(trancevibe_set_speed(tv, 0x0, 1) < 0)
		{
			printf("Cannot write to device\n");
		}
		trancevibe_close(tv);
	}
	return 0;
}
