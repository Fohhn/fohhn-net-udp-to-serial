/* Fohhn-Net */

#include "main.h"

#define SERIAL_BUF_LENGTH 515

const char *version_info = "1.6";

int main(int argc, char **argv)
{
  int opt;
  char *tty = NULL;
  int udp_port = 2101;
  int baud = 19200;
  int result;

  while ((opt = getopt(argc, argv, "t:p:b:hV")) != -1)
    switch (opt)
    {
    case 't':
      tty = optarg;
      break;
    case 'p':
      udp_port = atoi(optarg);
      break;
    case 'b':
      baud = atoi(optarg);
      break;
    case 'V':
      printf("%s version %s\n", argv[0], version_info);
      return 0;
      break;
    case 'h':
      usage(argv[0]);
      return 0;
    default:
      printf("try `%s -h' for more information\n", argv[0]);
      return 1;
    }

  if (udp_port < 1 || udp_port > 65535)
  {
    printf("invalid udp port\n");
    return 1;
  }

  if (tty == NULL)
  {
    usage(argv[0]);
    return 1;
  }

  clear_fdcp_buffers();

  result = init_serial_port(&uart, tty, baud);

  if (result == SERIAL_ERROR_BAUDRATE)
  {
    printf("no valid baud rate\n");
    return 1;
  }
  else if (result != SERIAL_OK)
  {
    printf("error opening serial device\n");
    return 1;
  }

  init_udp(&udp_socket, udp_port);

  printf("Starting Fohhn-Net forwarding at %d baud (fdcp version %s)\n", baud, version_info);

  select_loop();

  return 0;
}

int max(int x, int y)
{
  if (x > y)
    return x;
  else
    return y;
}

void select_loop()
{
  int maxfd, ready;
  struct timeval tv;
  fd_set fdset;
  FD_ZERO(&fdset);
  maxfd = max(udp_socket, uart) + 1;

  while (1)
  {
    FD_SET(udp_socket, &fdset);
    FD_SET(uart, &fdset);

    tv.tv_sec = 1;
    tv.tv_usec = 50000;

    ready = select(maxfd, &fdset, NULL, NULL, &tv);

    if (ready > 0)
    {
      if (FD_ISSET(udp_socket, &fdset))
      {
        udp_receive();
      }

      if (FD_ISSET(uart, &fdset))
      {
        serial_receive();
      }
    }
    else
    {
      reset_fdcp();
    }
  }
}

void serial_receive()
{
  unsigned char serial_buf[SERIAL_BUF_LENGTH];
  int len;

  len = read_from_serial_port(&uart, serial_buf, SERIAL_BUF_LENGTH);
  /* printf("received %d byte from serial port\n", len); */
  len = feed_reply_data(serial_buf, len);

  if (len > 0)
  {
    sendto(udp_socket, reply_buf, len, 0, (struct sockaddr *)&cli_addr, cli_addr_len);
    reset_fdcp();
  }
}

void udp_receive()
{

  int len;

  len = receive_from_udp(&udp_socket);      // receive from udp socket
  len = feed_request_data(udp_rx_buf, len); // check data

  if (len > 0)
  {
    reset_fdcp();
    write_to_serial_port(&uart, request_buf, len);
    fdcp_wait = 1;
  }
}

void usage(char *argv0)
{
  printf("Usage:\n");
  printf(" %s -t <tty>\n", argv0);
  printf("Options:\n");
  printf(" -t serial device\n");
  printf(" -p udp port\n");
  printf(" -b baud rate\n");
  printf(" -h show help\n");
  printf(" -V show version info\n");
}
