#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototype
int getMonthlySales();

int main() {
    srand(time(NULL)); // Seed random number generator

    int totalQuarter1 = 0, totalQuarter2 = 0, totalQuarter3 = 0, totalQuarter4 = 0;

    for (int month = 1; month <= 12; ++month) {
        int sales = getMonthlySales();
        
        switch (month) {
            case 1:
            case 2:
            case 3:
                totalQuarter1 += sales;
                break;
            case 4:
            case 5:
            case 6:
                totalQuarter2 += sales;
                break;
            case 7:
            case 8:
            case 9:
                totalQuarter3 += sales;
                break;
            case 10:
            case 11:
            case 12:
                totalQuarter4 += sales;
                break;
        }
    }

    printf("Total Sales Q1: %d\n", totalQuarter1);
    printf("Total Sales Q2: %d\n", totalQuarter2);
    printf("Total Sales Q3: %d\n", totalQuarter3);
    printf("Total Sales Q4: %d\n", totalQuarter4);

    return 0;
}

int getMonthlySales() {
    return rand() % 100001; // Random number between 0 and 100000
}