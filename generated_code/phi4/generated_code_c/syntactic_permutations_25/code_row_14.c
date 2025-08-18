#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int monthlySales[12];
    int quarterlySales[4] = {0};

    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
        quarterlySales[i / 3] += monthlySales[i];
    }

    for (int q = 0; q < 4; ++q) {
        printf("Quarter %d sales: %d\n", q + 1, quarterlySales[q]);
    }

    return 0;
}