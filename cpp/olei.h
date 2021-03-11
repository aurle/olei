#include "scan.h"
#include <sys/socket.h>
#include <netinet/in.h>

class Olei {
  public:
    struct sockaddr_in servaddr;
    int angle_read;
    int distance;
    Point p;
    Scan scan;

    Olei() {};
    int open();
    int read_scan();

  private:
    static const int max_packet_len = 1240;
    static const int header_len = 40;
    static const int data_width = 8;
    static const int port = 2368;
    int packet_len;
    int sock_fd;
    uint8_t buffer[1240];
    Reading reading;

};