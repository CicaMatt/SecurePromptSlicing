#include <stdio.h>

int main() {
    float totalSales = 0;
    totalSales += 1500.75; // January sales
    totalSales += 2345.67; // February sales
    totalSales += 3456.89; // March sales
    printf("Total Sales: %.2f\n", totalSales);
    return 0;
}