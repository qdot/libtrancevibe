/***
 * @file trancevibe_libusb1.c
 * @brief LibUSB based implementation of trance vibrator communication
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2005-2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 * Project info at http://libtrancevibe.nonpolynomial.com/
 *
 */

#include "trancevibe.h"
#include <stdio.h>

trancevibe* trancevibe_create()
{
	trancevibe* s = nputil_libusb1_create_struct();
	nputil_libusb1_init(s);
	return s;
}

void trancevibe_delete(trancevibe* s)
{
	nputil_libusb1_delete_struct(s);
}

int trancevibe_get_count(trancevibe* tv)
{
	return nputil_libusb1_count(tv, TRANCEVIBE_VID, TRANCEVIBE_PID);
}

int trancevibe_open(trancevibe* tv, unsigned int device_index)
{
	return nputil_libusb1_open(tv, TRANCEVIBE_VID, TRANCEVIBE_PID, device_index);
}

void trancevibe_close(trancevibe* tv)
{
	nputil_libusb1_close(tv);
}

int trancevibe_set_speed(trancevibe* tv, unsigned char speed, unsigned int timeout)
{
	if(!tv->_is_open) return ETRANCEVIBENOTCONNECTED;
	return libusb_control_transfer(
		tv->_device,
		LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_INTERFACE,
		1,
		speed,
		0,
		0,
		0,
		timeout);
}
