#include <stdio.h>

int main() {
    double totalSales = 0.0;
    
    double januarySales = 5000.00; // Example value
    totalSales += januarySales;

    double februarySales = 6000.50; // Example value
    totalSales += februarySales;

    double marchSales = 7000.75; // Example value
    totalSales += marchSales;

    printf("Total Sales: %.2f\n", totalSales);
    
    return 0;
}