#include "scan.h"
#include <stdio.h>

Scan::Scan() {};

int Scan::print()
{
    printf("\n| Angle | Distance |\n");
    for (int reading=0; reading < readings.size(); reading++) {
        printf(" %7.2f %6d\n", readings[reading].angle, readings[reading].distance);
    }
    return 1;
}