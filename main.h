/*
 * Copyright 2023 Fohhn
 *
 * licensed under the MIT License, see LICENSE for more information
 */

#ifndef __MAIN_H
#define __MAIN_H

#include "fdcp_forward.h"
#include "udp.h"
#include "serial.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int udp_socket;
int uart;

int max(int x, int y);
void usage(char *argv0);
void udp_receive();
void serial_receive();
void select_loop();

#endif // __MAIN_H
