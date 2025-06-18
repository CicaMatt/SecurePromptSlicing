#include <stdlib.h> //for srand and rand functions
#include <stdio.h>  //for printf function
#include <time.h>   //for time function

//function prototype
float getMonthlySales();

int main(void) {
    float sales[4];

    // seed the randomizer
    srand((unsigned int)time(NULL));
    
    for (int month = 0; month < 12; month++) {
        //call getMonthlySales function and store result in sales array
        sales[month / 3] += getMonthlySales();
    }

    //print quarterly sales
    printf("Quarterly sales:\n");
    for (int qtr = 0; qtr < 4; qtr++) {
        printf("%.2f\n", sales[qtr]);
    }
}

float getMonthlySales() {
    //return a random number between 1,000 and 5,000
    return (rand() % 4000 + 1) + 1000;
}