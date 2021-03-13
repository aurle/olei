#include "olei.h"

int main(void)
{
  Olei olei;
  olei.open();
  olei.scan.end = 135;
  olei.scan.start = -olei.scan.end;

    while (1)
    {
        olei.read_scan();
        //olei.scan.print(); //Enable this to see the actual readings
        olei.scan.plot(); //Enable this to see a graphical view of the lidar
    }
}
