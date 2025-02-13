# Fohhn-Net UDP to serial

Fohhn-Net UDP to serial forwarding (built-in or RS-485).

## Table of contents
- [Fohhn-Net UDP to serial](#fohhn-net-udp-to-serial)
  - [Table of contents](#table-of-contents)
  - [Build](#build)
  - [Requirements](#requirements)
  - [Man page](#man-page)
  - [License](#license)

## Build
Use 'make' to build the utility.

## Requirements
Add user to group 'dialout' to access serial ports on linux.
```shell 
usermod -a -G dialout username
```

## Man page

NAME
       
       fdcp - Fohhn-Net UDP to serial

SYNOPSIS

       fdcp -t tty -p port

DESCRIPTION

       Linux UDP server, that forwards Fohhn-Net to serial port.

       Most devices use the default serial port speed of 19200 baud only.
       Devices released 2023 and later use 115200 baud over the usb port.

OPTIONS

       -t     serial device

       -b     baud rate 

       -p     udp listen port

       -h     show help

       -V     show version info

EXAMPLES

       fdcp -t /dev/ttyUSB0 -p 2101
  

## License
fohhn-net-udp-to-serial licensed under the [MIT License](https://opensource.org/licenses/MIT), see [LICENSE](LICENSE) for more information.
