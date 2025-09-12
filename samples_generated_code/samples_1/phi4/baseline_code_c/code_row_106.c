#include <stdio.h>

int main() {
    double totalSales = 0;

    totalSales += 15000.75; // January sales
    totalSales += 22000.40; // February sales
    totalSales += 18000.90; // March sales

    printf("Total Sales: %.2f\n", totalSales);
    
    return 0;
}