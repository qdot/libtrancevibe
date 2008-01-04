/*
 * Declaration file for Trancevibrator User Space Driver
 *
 * Copyright (c) 2005-2008 Kyle Machulis/Nonpolynomial Labs <kyle@nonpolynomial.com> (http://www.nonpolynomial.com)
 *
 * More info on Nonpolynomial Labs @ http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libtrancevibe/
 *
 * This library is covered by the MIT License, read LICENSE.txt for details.
 */

#ifndef LIBTRANCEVIBE_H
#define LIBTRANCEVIBE_H

/// USB Vendor ID for the Trance Vibrator
#define TRANCEVIBE_VID 0x0b49

/// USB Product ID for the Trance Vibrator
#define TRANCEVIBE_PID 0x064f

/// Error code for non-connected trancevibes
#define ETRANCEVIBENOTCONNECTED -5

#include "usb.h"

/// Typedef for the libusb handle, to make code more readable
typedef usb_dev_handle* trancevibe; 

/** 
 * Counts trancevibes connected to the USB busses on the system
 * 
 * 
 * @return Number of trancevibes connected
 */
int trancevibe_get_count();

/** 
 * Opens the device
 * 
 * @param tv Pointer to store opened device handle
 * @param device_index Index of the device to open (for multiple devices)
 * 
 * @return device_index on success, libusb error or ETRANCEVIBENOTCONNECTED on error
 */
int trancevibe_open(trancevibe* dev, unsigned int device_index);

/** 
 * Closes trancevibe passed to it
 * 
 * @param tv Trancevibe handle to close
 */
void trancevibe_close(trancevibe dev);

/** 
 * Sets speed for the trance vibrator handle passed to it
 * 
 * @param tv Trancevibe handle to send speed to
 * @param speed Speed value to set, 0 is minimum, 255 is maximum
 * @param timeout Timeout value for speed setting. Should be at least 1.
 * 
 * @return 0 or greater on success, libusb error or ETRANCEVIBENOTCONNECTED on error
 */
int trancevibe_set_speed(trancevibe dev, unsigned char speed, unsigned int timeout);

#endif //LIBTRANCEVIBE_H
