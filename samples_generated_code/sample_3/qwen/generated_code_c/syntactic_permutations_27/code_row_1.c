#include <stdio.h>

int main() {
    float totalSales;
    totalSales = 1500.75; // Example sales for January
    totalSales += 2345.60; // Example sales for February
    totalSales += 1987.50; // Example sales for March
    printf("%.2f\n", totalSales);
    return 0;
}