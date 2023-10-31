/*
 * Copyright 2023 Fohhn
 *
 * licensed under the MIT License, see LICENSE for more information
 */

#include "fdcp_forward.h"

uint8_t request_buf[REQUEST_BUF_LEN];
uint8_t reply_buf[REPLY_BUF_LEN];
uint8_t fdcp_wait;
int fdcp_pos;

void clear_fdcp_buffers()
{
  fdcp_wait = 0;
  fdcp_pos = 0;

  memset(request_buf, 0, REQUEST_BUF_LEN);
  memset(reply_buf, 0, REPLY_BUF_LEN);
}

void reset_fdcp()
{
  fdcp_wait = 0;
  fdcp_pos = 0;
}

int feed_request_data(uint8_t *data, int len)
{
  int result = 0;

  if (len > 0 && len <= REQUEST_BUF_LEN)
  {
    if (data[0] == FDCP_START_BYTE)
    {
      reset_fdcp();
      memcpy(request_buf, data, len);
      result = len;
    }
  }

  return result;
}

int feed_reply_data(uint8_t *data, int len)
{
  int i;
  int reply_len = 0;

  if (len > 0)
  {
    if (fdcp_wait)
    {
      for (i = 0; i < len; i++)
      {
        reply_buf[fdcp_pos] = data[i];

        if (reply_buf[fdcp_pos] == FDCP_END_BYTE)
        {
          reply_len = fdcp_pos + 1;
          break;
        }

        fdcp_pos++;
        if (fdcp_pos > REPLY_BUF_LEN)
          reset_fdcp();
      }
    }
  }
  return reply_len;
}
