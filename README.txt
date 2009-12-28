=============
libtrancevibe
=============

by Kyle Machulis <kyle@nonpolynomial.com>
Nonpolynomial Labs - http://www.nonpolynomial.com

===========
Description
===========

libtrancevibe is a C-based development library for the Rez Trancevibrator, a USB powered and controlled vibrator originally distributed for use with the game Rez for the Playstation2. 

libtrancevibe works with both the original ASCII Rez Trancevibrator, as well as the Drmn Trance Vibrator (http://tim.cexx.org/projects/vibe/)

===========================
Trance Vibrator Information
===========================

More information about the TranceVibrator can be found at 

http://wiki.opendildonics.org/Rez_TranceVibrator

====================
Library Requirements
====================

Requires libusb and cmake (for building)

------
libusb-1.0 (Linux and OS X)
------

http://www.libusb.org

------
libusb-win32 (Windows, legacy until winusb supported in libusb-1.0)
------

http://libusb-win32.sourceforge.net/

-----
cmake
-----

http://www.cmake.org

==================
Platform Specifics
==================

-------
Windows
-------

- If the write timeout on windows is set to 0, writes will be quite flakey and will fail often. Always set it to at least 5.

- Windows requires a libusb-win32 based filter driver for the trance vibrator. A prebuilt version is available from the libtrancevibe download site.

-----
Linux
-----

- If the write timeout on linux is set to < 10, writes will return false negatives and will fail sometimes. Always set it to at least 10.

- Running libusb access under Linux will either require running as root or reconfiguring USB device permissions. More information on this can be found at:

http://www.gphoto.org/doc/manual/permissions-usb.html

