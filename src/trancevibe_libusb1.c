/***
 * @file trancevibe_libusb1.c
 * @brief LibUSB based implementation of trance vibrator communication
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2005-2010 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 * Project info at http://libtrancevibe.nonpolynomial.com/
 *
 */


#include "trancevibe.h"
#include "nputil/nputil_libusb1.h"
#include <stdio.h>

#define NPUTIL_DEVICE_NAME trancevibe
#define NPUTIL_USB_VID TRANCEVIBE_VID
#define NPUTIL_USB_PID TRANCEVIBE_PID

#include "nputil_libusb1.c"

int trancevibe_set_speed(trancevibe* tv, unsigned char speed, unsigned int timeout)
{
	if(!tv->_is_open) return E_NPUTIL_NOT_OPENED;
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
