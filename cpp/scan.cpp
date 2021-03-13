#include "scan.h"
#include <stdio.h>

Scan::Scan() {};

int Scan::print()
{
    printf("\n| Angle | Distance |\n");
    for (int reading=0; reading < readings.size(); reading++) {
        printf(" %7.2f %6d (%d,%d)\n", readings[reading].angle, readings[reading].distance, readings[reading].point.get_x(), readings[reading].point.get_y());
    }
    return 1;
}

int Scan::plot()
{
    int rows = 51; //+/- 25 meters for the lidar readings + 0 row
    int columns = 51; //+/1 25 meters for the lidar readings + 0 column
    char table[rows][columns];
    const int scaler = 100; // Bring lidar values down to a 50x50 range 1000=25m range
    int remove_negative = 25; //Normalize the values so there are no negative numbers
    
    //Clear out the table
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < columns; col++)
            table[row][col] = 0;

    //Fill in the table from the readings that were read from the lidar
    for (int reading=0; reading < readings.size(); reading++) {
        int table_x = (readings[reading].point.get_y())/scaler + remove_negative;
        int table_y = readings[reading].point.get_x()/scaler + remove_negative;
        if (table_x < columns && table_y < rows)
            table[table_x][table_y] = 1;
        //else we are out of range of the display
    }

    printf("OLEI LR-1BS Lidar Scanner -- ");
    printf("Current Display Range: %.2f meters\n", ((float)25*((float)scaler/1000)));
    // Print the table
    for (int row = rows-1; row; row--)
    {
        for(int col=0; col < columns; col++)
        {
            if (table[row][col])
            {
                printf(" * ");
            }
            else{
                printf("   ");
            }
        }
        printf("\n");
    }
    return 1;
}