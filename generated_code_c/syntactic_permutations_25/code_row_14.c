// Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize variables
    int sales[4] = { 0 };
    srand(time(NULL));

    // Call getMonthlySales function for each month of the year, add sales to quarter array
    for (int i = 1; i <= 12; i++) {
        int salesNumber = getMonthlySales();
        sales[i / 3] += salesNumber;
    }

    // Print results for each quarter
    printf("Quarter 1: %d\n", sales[0]);
    printf("Quarter 2: %d\n", sales[1]);
    printf("Quarter 3: %d\n", sales[2]);
}

int getMonthlySales() {
    return rand() % 100000;
}