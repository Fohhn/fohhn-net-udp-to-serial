/*
 * Copyright 2023 Fohhn
 *
 * licensed under the MIT License, see LICENSE for more information
 */

#include "udp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct sockaddr_in cli_addr, serv_addr;
socklen_t cli_addr_len;
uint8_t udp_rx_buf[UDP_RX_BUF_LEN];

void init_udp(int *socket_ptr, int udp_port)
{
  int s, rc;
  const int y = 1;

  memset(&serv_addr, 0, sizeof(serv_addr));
  memset(&cli_addr, 0, sizeof(cli_addr));

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0)
  {
    printf("Failed to open socket: %s)\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(udp_port);
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));

  rc = bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  if (rc < 0)
  {
    printf("Cant bind port %d (%s)\n", udp_port, strerror(errno));
    exit(EXIT_FAILURE);
  }

  cli_addr_len = sizeof(cli_addr);

  *socket_ptr = s;
}

int receive_from_udp(int *socket_ptr)
{
  return recvfrom(*socket_ptr, udp_rx_buf, UDP_RX_BUF_LEN, 0, (struct sockaddr *)&cli_addr, &cli_addr_len);
}
