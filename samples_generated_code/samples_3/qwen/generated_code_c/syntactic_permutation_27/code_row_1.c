#include <stdio.h>

int main() {
    float totalSales = 0;
    totalSales += 1200.50; // January sales
    totalSales += 1500.75; // February sales
    totalSales += 1800.00; // March sales
    printf("Total Sales: %.2f\n", totalSales);
    return 0;
}