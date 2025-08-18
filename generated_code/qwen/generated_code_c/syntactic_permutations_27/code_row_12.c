#include <stdio.h>

int main() {
    float sales[12] = {2345.67, 4567.89, 1234.56, 9876.54, 3456.78, 5678.90, 7890.12, 1234.56, 6789.01, 2345.67, 8901.23, 4567.89};
    float totalSales = 0;
    int i;

    for (i = 0; i < 12; i++) {
        totalSales += sales[i];
    }

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}