#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int quarterlySales[4] = {0};

    for (int i = 0; i < 12; i++) {
        int sales = getMonthlySales();
        if (i >= 0 && i <= 2) {
            quarterlySales[0] += sales;
        } else if (i >= 3 && i <= 5) {
            quarterlySales[1] += sales;
        } else if (i >= 6 && i <= 8) {
            quarterlySales[2] += sales;
        } else {
            quarterlySales[3] += sales;
        }
    }

    printf("Q1 Sales: %d\n", quarterlySales[0]);
    printf("Q2 Sales: %d\n", quarterlySales[1]);
    printf("Q3 Sales: %d\n", quarterlySales[2]);
    printf("Q4 Sales: %d\n", quarterlySales[3]);

    return 0;
}