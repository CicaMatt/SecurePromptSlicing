#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    
    int sales[12];
    for (int i = 0; i < 12; ++i) {
        sales[i] = getMonthlySales();
    }

    printf("Quarter 1 Sales: %d\n", sales[0] + sales[1] + sales[2]);
    printf("Quarter 2 Sales: %d\n", sales[3] + sales[4] + sales[5]);
    printf("Quarter 3 Sales: %d\n", sales[6] + sales[7] + sales[8]);
    printf("Quarter 4 Sales: %d\n", sales[9] + sales[10] + sales[11]);

    return 0;
}