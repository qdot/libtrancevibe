/*
 *  trancevibratortest.cpp
 *  libtrancevibrator
 *
 *  Created by qdot on 11/2/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
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

		trancevibe_set_speed(tv, 0xff, 1);
#ifndef WIN32
		sleep(1);
#elif WIN32
		Sleep(1000);
#endif
		trancevibe_set_speed(tv, 0x00, 1);
		trancevibe_close(tv);
	}
	return 0;
}
