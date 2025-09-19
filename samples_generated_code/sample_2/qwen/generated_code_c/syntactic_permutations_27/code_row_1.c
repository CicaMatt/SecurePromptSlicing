#include <stdio.h>

int main() {
    float totalSales;
    totalSales = 1000.50; // Example sales for January
    totalSales += 1200.75; // Example sales for February
    totalSales += 950.25;  // Example sales for March
    printf("%.2f\n", totalSales);
    return 0;
}