#include <stdio.h>

int main() {
    double monthlySales[3] = {1200.50, 2300.75, 1450.00};
    double totalSales = 0;
    
    for (int i = 0; i < 3; i++) {
        totalSales += monthlySales[i];
    }

    printf("Total Sales: %.2f\n", totalSales);

    return 0;
}