#include <stdio.h>

int main() {
    double totalSales = 0.0;
    
    totalSales += 100.50;
    totalSales += 200.75;
    totalSales += 300.25;

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}