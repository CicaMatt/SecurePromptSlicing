#include <stdio.h>

int main() {
    int monthlySales[] = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650};
    int totalSales = 0;
    for (int i = 0; i < 12; ++i) {
        totalSales += monthlySales[i];
    }
    printf("Total Sales: %d\n", totalSales);
    return 0;
}