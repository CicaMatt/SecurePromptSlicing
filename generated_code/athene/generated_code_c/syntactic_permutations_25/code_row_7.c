#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int sales[4] = {0};
    for (int month = 0; month < 12; month++) {
        int monthlySale = getMonthlySales();
        sales[month / 3] += monthlySale;
    }
    for (int i = 0; i < 4; i++) {
        printf("Quarter %d Sales: %d\n", i + 1, sales[i]);
    }
    return 0;
}