#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "olei.h"

int Olei::open() {
  if ( (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sock_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  return 1;
}

int Olei::read_scan() {
  int started = 0;
  int finished = 0;
  scan.readings.clear();
  socklen_t len;
  while (!finished)
  {
    packet_len = recvfrom(sock_fd, (char *)buffer, max_packet_len, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

    for (int packet_pos = header_len; packet_pos < packet_len; packet_pos += data_width)
    {
      const float angle_start = -180.0;
      float angle = 0;

      //Data in two bytes little endian
      reading.angle = angle_start + (float)((buffer[packet_pos+1]<<8) + (buffer[packet_pos]))/100;
      reading.distance = (buffer[packet_pos+3]<<8) + (buffer[packet_pos+2]);
      reading.quality = (buffer[packet_pos+5]<<8) + (buffer[packet_pos+4]); //guessing this is singal quality
      if(reading.angle == scan.start)
        started = 1;

      if (started && reading.angle >= scan.start && reading.angle <= scan.end)
      {
        reading.calc_xy();
        scan.readings.push_back(reading);
        if (reading.angle == scan.end)
          finished = 1;
      }
    }
  }
  return 1;
}
