/*
 * Exercise 4.22 on page 196
 * Help: https://www.geeksforgeeks.org/estimating-value-pi-using-monte-carlo/
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define INTERVAL 1000

int main()
{
    int circle_points = 0, square_points = 0;
    int interval, count;
    double rand_x, rand_y;
    double origin_dist;
    double pi;
    double x, y;

    srand(time(NULL));
    
    for(count = 0; count < (INTERVAL * INTERVAL); count++) {
        rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL;
        
        origin_dist = rand_x * rand_x + rand_y * rand_y;
        
        if(origin_dist <= 1) {
            circle_points++;
        }
        
        square_points++;
        
        pi = (double)(4 * circle_points) / square_points;
        
        printf("rand_x %f, rand_y %f, circle_points %d, square_points %d, pi %f\n", rand_x, rand_y, circle_points, square_points, pi);
    }
    
    return 0;
}
