#include "reading.h"
#include <vector>


/** A scan of the lidar */
class Scan {
    public:
        std::vector<Reading> readings; /// readings for one scan of the lidar
        int start; ///start of the scan in degres clockwise of forward
        int end; ///end of the can in degrees counter clockwise of forward.o

        Scan();

        int print();
};