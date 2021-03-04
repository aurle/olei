/** Read data from an OLEI lidar */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>

#define MAX_SIZE 1240
#define PORT 2368

int main(void)
{
  int sockfd;
  uint8_t buffer[MAX_SIZE];
  struct sockaddr_in servaddr;

  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
        
  int packet_size;
  socklen_t len;

  while(1) {
    packet_size = recvfrom(sockfd, (char *)buffer, MAX_SIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
    const int header_len = 40;
    const int data_width = 8;

    for (int packet_pos=header_len; packet_pos < packet_size; packet_pos+=data_width)
    {
      int reading;
      int raw_angle, distance, number3;
      
      const float start_angle = -180;
      float angle = 0;

      raw_angle = (buffer[packet_pos+1]<<8) + (buffer[packet_pos]);
      distance = (buffer[packet_pos+3]<<8) + (buffer[packet_pos+2]);
      number3 = (buffer[packet_pos+5]<<8) + (buffer[packet_pos+4]);

      const int start_range =- 135;
      const int end_range = -start_range;

      angle = start_angle + (float)raw_angle/100;
      if (angle == start_range)
        printf("\n| Angle | Distance |\n");
      if (angle >= start_range && angle <= end_range)
        printf("%.2f %d\n", angle, distance);
    }
  }
}
