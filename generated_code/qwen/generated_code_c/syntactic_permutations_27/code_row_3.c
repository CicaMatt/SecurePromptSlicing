#include <stdio.h>

int main() {
    float totalSales;
    totalSales = 0.0 + 12345.67; // January sales
    totalSales += 23456.78;       // February sales
    totalSales += 34567.89;       // March sales
    printf("Total Sales: %.2f\n", totalSales);
    return 0;
}