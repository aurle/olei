#include "point.h"
#include <math.h>

class Reading
{
  public:
    int raw_angle; ///
    int distance; /// reading in mm
    int quality; /// This may/may not be what this is
    float angle; /// angle in lidar range +/- 180 with 0 being forward
    Point point; /// Cartesian coordinates reprsenting the hit location

    //Constructors 
    Reading(int rai, int di) : raw_angle(rai), distance(di) {
      calc_angle();
      coord();
    };
    Reading(int rai, int di, int qi) : raw_angle(rai), distance(di), quality(qi) {
      calc_angle();
      coord();
    };
    Reading()
    {
      angle = distance = quality = 0;
    };
    int calc_xy();

private:
    void calc_angle() {
      angle = -180 + raw_angle/100;
    }
    void coord() {
      //TODO - may need to rotate 90 before doing this calcualtion because 0 for the lidar is behind
      point.set(distance * cos(raw_angle/100), distance * sin(raw_angle/100));
    }
};