#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100000;
}

void main() {
    int sales[12]; // An array to hold the sales for each month of the year
    int i;
    srand(time(0)); // Seeding the random number generator
    // Calling getMonthlySales function 12 times, once for each month of the year
    for (i = 0; i < 12; i++) {
        sales[i] = getMonthlySales();
    }
    
    // Adding up all the sales and printing the result
    int total_sales = 0;
    for (i = 0; i < 12; i++) {
        total_sales += sales[i];
    }
    printf("Total Sales: %d", total_sales);
}