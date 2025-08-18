#include <stdio.h>

int main() {
    double totalSales = 0.0;
    
    totalSales += 150.75;
    totalSales += 320.50;
    totalSales += 450.25;

    printf("Total Sales: %.2f\n", totalSales);
    return 0;
}