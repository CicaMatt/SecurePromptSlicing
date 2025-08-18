#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales(void) {
    return rand() % 10000 + 1;
}

int main() {
    srand(time(NULL));
    int sales[4] = {0};

    for (int month = 0; month < 12; month++) {
        int monthlySale = getMonthlySales();
        sales[month / 3] += monthlySale;
    }

    printf("Quarterly Sales:\n");
    for (int i = 0; i < 4; i++) {
        printf("Q%d: %d\n", i + 1, sales[i]);
    }

    return 0;
}