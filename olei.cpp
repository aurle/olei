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

#define MAX_SIZE 4096
#define PORT 2368

int main(void)
{
  int sockfd;
  uint8_t buffer[MAX_SIZE];
  struct sockaddr_in servaddr;
  //short reading[460];
  //uint8_t strength[460]

  printf("Inside Main\n");

  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("192.168.1.100");

  int bind_result=bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
        
  printf("Bind result %d\n",bind_result);


  int n;
  socklen_t len;

  int reading_num = 0;
  printf("Entering While Loop\n");
  while(1) {
    n = recvfrom(sockfd, (char *)buffer, MAX_SIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
    printf("\n\nread %d bytes\n\n", n);
    int id = (buffer[3]<<8) + buffer[2];
    int protocol = (buffer[5]<<8) + buffer[4];
    char identifier[11];

    for (int i=0; i < n; i++)
    {
      printf("%02x ", buffer[i]&0xFF);
    }

    strncpy(identifier, (char *)&buffer[7], 10);
    identifier[10] = '\0';

    printf("id? 0x%04x\n", id);
    printf("protocol 0x%04x\n", protocol);
    printf("Identifier %s\n", identifier);


    //int id = buffer[] 
    for (int i=40,j=0; i < n; i+=8,j++)
    {
      int reading;
      int number1, number2, number3;
      
      /*
      number1 = (buffer[i+3]<<16) + (buffer[i+2]<<8) + (buffer[i+1]);
      number2 = (buffer[i+5]<<8) + (buffer[i+4]);
      number3 = (buffer[i+6]);
*/
      number1 = (buffer[i+1]<<8) + (buffer[i]);
      if (number1==0)
         reading_num=0;
      else
         reading_num++;
      number2 = (buffer[i+3]<<8) + (buffer[i+2]);
      number3 = (buffer[i+5]<<8) + (buffer[i+4]);
      
      printf("%d %d %d %d -- ", reading_num, number1, number2, number3);
       
      for(int byte = 0; byte<8; byte++)
      {
        printf("%02x ", buffer[i+byte]);
      }
      printf("\n");

    }

  }
}
