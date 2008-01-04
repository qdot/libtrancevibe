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

/** 
 * libusb initialization function
 * 
 */
void trancevibe_init_usb()
{
	usb_init();
    usb_find_busses();
    usb_find_devices();
	gIsInitialized = 1;
}

/** 
 * Counts trancevibes connected to the USB busses on the system
 * 
 * 
 * @return Number of trancevibes connected
 */
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

/** 
 * Opens the device
 * 
 * @param tv Pointer to store opened device handle
 * @param device_index Index of the device to open (for multiple devices)
 * 
 * @return device_index on success, libusb error or ETRANCEVIBENOTCONNECTED on error
 */
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
	return ETRANCEVIBENOTCONNECTED;
}

/** 
 * Closes trancevibe passed to it
 * 
 * @param tv Trancevibe handle to close
 */
void trancevibe_close(trancevibe tv)
{
	if(!tv) return;
	usb_close(tv);
}

/** 
 * 
 * 
 * @param tv Trancevibe handle to send speed to
 * @param speed Speed value to set, 0 is minimum, 255 is maximum
 * @param timeout Timeout value for speed setting. Should be at least 1.
 * 
 * @return 0 or greater on success, libusb error or ETRANCEVIBENOTCONNECTED on error
 */
int trancevibe_set_speed(trancevibe tv, unsigned char speed, unsigned int timeout)
{
	if(!tv) return ETRANCEVIBENOTCONNECTED;
	return usb_control_msg(tv, USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE, 1, speed, 0, 0, 0, timeout);
}
