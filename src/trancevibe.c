/*
 * Implementation file for Trancevibrator User Space Driver
 *
 * Copyright (c) 2005-2007 Kyle Machulis/Nonpolynomial Labs <kyle@nonpolynomial.com>  
 *
 * More info on Nonpolynomial Labs @ http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libtrancevibe/
 *
 * This library is covered by the MIT License, read LICENSE.txt for details.
 */

#include "trancevibe.h"

char gIsInitialized = 0;

void trancevibe_init_usb()
{
	usb_init();
    usb_find_busses();
    usb_find_devices();
	gIsInitialized = 1;
}

int trancevibe_get_count()
{
	int device_count = 0;	
	struct usb_bus* bus;
	struct usb_device* dev;
	
	if(!gIsInitialized)
	{
		trancevibe_init_usb();
	}
	for (bus = usb_get_busses(); bus != 0; bus = bus->next) 
	{			
		for (dev = bus->devices; dev != 0; dev = dev->next) 
		{	
			if (dev->descriptor.idVendor == TRANCEVIBE_VID && dev->descriptor.idProduct == TRANCEVIBE_PID)
			{
				++device_count;
			}
		}
	}
	return device_count;
}

int trancevibe_open(trancevibe* tv, unsigned int device_index)
{
	int device_count = 0;
	struct usb_bus* bus;
	struct usb_device* dev;
	
	if(!gIsInitialized)
	{
		trancevibe_init_usb();
	}

	for (bus = usb_get_busses(); bus != 0; bus = bus->next) 
	{			
		for (dev = bus->devices; dev != 0; dev = dev->next) 
		{	
			if (dev->descriptor.idVendor == TRANCEVIBE_VID && 
				dev->descriptor.idProduct == TRANCEVIBE_PID)
			{
				if(device_count == device_index)
				{
					*tv = usb_open(dev);
					if (tv) 
					{
						return device_count;
					}
				}
				++device_count;
			}
		}
	}	
	return -1;
}

int trancevibe_close(trancevibe tv)
{
	if(!tv) return -1;
	usb_close(tv);
	return 0;
}

int trancevibe_set_speed(trancevibe tv, unsigned char speed, unsigned int timeout)
{
	if(!tv) return -1;
	return usb_control_msg(tv, USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE, 1, speed, 0, 0, 0, timeout);
}
