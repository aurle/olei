#include "point.h"

Point::Point() {};
    
Point::Point(int xi, int yi) : x(xi), y(yi) {};

int Point::set (int x_set, int y_set) {
    x = x_set;
    y = y_set;
    return 1;
}

int Point::clear () {
    x = y = 0;
    return 1;
}

int Point::get_x() {
    return x;
}

int Point::get_y() {
    return y;
}

