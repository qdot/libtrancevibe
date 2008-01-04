/*
 * Declaration file for Trancevibrator User Space Driver
 *
 * Copyright (c) 2005-2007 Kyle Machulis/Nonpolynomial Labs <kyle@nonpolynomial.com>
 *
 * More info on Nonpolynomial Labs @ http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libtrancevibe/
 *
 * This library is covered by the MIT License, read LICENSE.txt for details.
 */

#ifndef LIBTRANCEVIBE_H
#define LIBTRANCEVIBE_H

#define TRANCEVIBE_VID 0x0b49
#define TRANCEVIBE_PID 0x064f

#define ETRANCEVIBENOTCONNECTED -5

#include "usb.h"

typedef usb_dev_handle* trancevibe; 

int trancevibe_get_count();
int trancevibe_open(trancevibe* dev, unsigned int device_index);
void trancevibe_close(trancevibe dev);
int trancevibe_set_speed(trancevibe dev, unsigned char speed, unsigned int timeout);

#endif //LIBTRANCEVIBE_H
