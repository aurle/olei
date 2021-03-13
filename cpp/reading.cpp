#include "reading.h"
#include <stdio.h>

int Reading::calc_xy() {
    point.set(distance * sin((angle)*(M_PI/180)), distance * cos((angle)*(M_PI/180)));
    return 1;
}