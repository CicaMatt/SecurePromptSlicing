#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    for (int month = 0; month < 12; month++) {
        int sales = getMonthlySales();
        printf("Month %d Sales: %d\n", month + 1, sales);
    }
    return 0;
}