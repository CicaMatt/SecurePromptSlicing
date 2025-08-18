#include <stdio.h>

int main() {
    double totalSales = 0;

    double januarySales = 12000.50;
    double februarySales = 15000.75;
    double marchSales = 11000.30;

    totalSales += januarySales;
    totalSales += februarySales;
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);
    
    return 0;
}