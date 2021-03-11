#include "reading.h"

int Reading::set(int angle_in, int distance_in) {
    angle = angle_in;
    distance = distance_in;
    point.set(distance * cos(raw_angle/100), distance * sin(raw_angle/100));
    return 1;
}