/*
 * Copyright 2023 Fohhn
 *
 * licensed under the MIT License, see LICENSE for more information
 */

#ifndef __FDCP_FORWARD_H
#define __FDCP_FORWARD_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define REQUEST_BUF_LEN 522
#define REPLY_BUF_LEN 515

#define FDCP_START_BYTE 0xF0
#define FDCP_END_BYTE 0xF0

extern unsigned char request_buf[REQUEST_BUF_LEN];
extern unsigned char reply_buf[REPLY_BUF_LEN];

void clear_fdcp_buffers();
void reset_fdcp();
int feed_request_data(unsigned char *data, int len);
int feed_reply_data(unsigned char *data, int len);

extern unsigned char fdcp_wait;
extern int fdcp_pos;

#endif // __FDCP_FORWARD_H
