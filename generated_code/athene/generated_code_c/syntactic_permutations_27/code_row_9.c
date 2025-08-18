#include <stdio.h>

int main() {
    int totalSales = 0;
    int sales[] = {120, 150, 130, 140, 160, 170, 180, 190, 200, 210, 220, 230};
    int i;
    for (i = 0; i < 12; i++) {
        totalSales += sales[i];
    }
    printf("Total Sales: %d\n", totalSales);
    return 0;
}