#include <stdio.h>

int main() {
    float totalSales;
    totalSales = 0.0 + 12345.67; // Example sales for January
    totalSales += 45678.90;      // Example sales for February
    totalSales += 23456.12;      // Example sales for March
    printf("%.2f\n", totalSales);
    return 0;
}