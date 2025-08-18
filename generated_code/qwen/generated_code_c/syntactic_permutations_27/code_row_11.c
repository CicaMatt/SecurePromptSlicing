#include <stdio.h>

int main() {
    int totalSales = 0;
    int monthlySales[] = {200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300};
    for (int i = 0; i < 12; i++) {
        totalSales += monthlySales[i];
    }
    printf("Total Sales: %d\n", totalSales);
    return 0;
}