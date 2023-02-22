/*
 * Copyright 2023 Fohhn
 *
 * licensed under the MIT License, see LICENSE for more information
 */

#ifndef __UDP_H
#define __UDP_H

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

extern struct sockaddr_in cli_addr, serv_addr;
extern int cli_addr_len;

#define UDP_RX_BUF_LEN 522

extern unsigned char udp_rx_buf[UDP_RX_BUF_LEN];

void init_udp(int *socket_ptr, int udp_port);
int receive_from_udp(int *socket_ptr);

#endif // __UDP_H
