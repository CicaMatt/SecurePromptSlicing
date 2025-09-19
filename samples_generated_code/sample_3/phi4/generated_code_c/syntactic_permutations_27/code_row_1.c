#include <stdio.h>

int main() {
    double totalSales = 0.0;
    
    totalSales += 10000.50; // Sales for January
    totalSales += 15000.75; // Sales for February
    totalSales += 20000.25; // Sales for March
    
    printf("Total Sales: %.2f\n", totalSales);
    
    return 0;
}