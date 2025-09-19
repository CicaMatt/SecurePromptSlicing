#include <stdio.h>

int main() {
    double totalSales = 0.0;

    totalSales += 15000.50; // January sales
    totalSales += 20000.75; // February sales
    totalSales += 25000.25; // March sales

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}