/***
 * @file trancevibe.h
 * @brief LibUSB based implementation of trance vibrator communication
 * @author Kyle Machulis (kyle@nonpolynomial.com)
 * @copyright (c) 2005-2009 Nonpolynomial Labs/Kyle Machulis
 * @license BSD License
 *
 * Project info at http://libtrancevibe.nonpolynomial.com/
 *
 */

#ifndef LIBTRANCEVIBE_H
#define LIBTRANCEVIBE_H

/// USB Vendor ID for the Trance Vibrator
#define TRANCEVIBE_VID 0x0b49

/// USB Product ID for the Trance Vibrator
#define TRANCEVIBE_PID 0x064f

/// Error code for non-connected trancevibes
#define E_NPUTIL_DRIVER_ERROR -1
#define E_NPUTIL_NOT_INITED -2
#define E_NPUTIL_NOT_OPENED -3

/// Typedef for nputil struct, to make code more readable
typedef struct {
	struct libusb_context* _context;
	struct libusb_device_handle* _device;
	struct libusb_transfer* _in_transfer;
	struct libusb_transfer* _out_transfer;
	int _is_open;
	int _is_inited;
} trancevibe;

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Creates a trancevibrator struct for usage
 * 
 * 
 * @return A pointer to a trancevibrator struct
 */
	trancevibe* trancevibe_create();

/** 
 * Deletes a trancevibrator struct from memory when finished
 * 
 */
	void trancevibe_delete(trancevibe* dev);

/** 
 * Counts trancevibes connected to the USB busses on the system
 * 
 * 
 * @return Number of trancevibes connected
 */
	int trancevibe_get_count(trancevibe* dev);

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
	int trancevibe_close(trancevibe* dev);

/** 
 * Sets speed for the trance vibrator handle passed to it
 * 
 * @param tv Trancevibe handle to send speed to
 * @param speed Speed value to set, 0 is minimum, 255 is maximum
 * @param timeout Timeout value for speed setting. Should be at least 1.
 * 
 * @return 0 or greater on success, libusb error or ETRANCEVIBENOTCONNECTED on error
 */
	int trancevibe_set_speed(trancevibe* dev, unsigned char speed, unsigned int timeout);

#ifdef __cplusplus
}
#endif
	
#endif //LIBTRANCEVIBE_H
