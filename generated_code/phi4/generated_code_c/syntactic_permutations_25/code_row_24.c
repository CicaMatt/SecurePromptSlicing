#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int monthlySales[12];
    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
    }

    int quarterlySales[4] = {0};

    for (int i = 0; i < 3; ++i) {
        quarterlySales[i] += monthlySales[i];
    }
    for (int i = 3; i < 6; ++i) {
        quarterlySales[1] += monthlySales[i];
    }
    for (int i = 6; i < 9; ++i) {
        quarterlySales[2] += monthlySales[i];
    }
    for (int i = 9; i < 12; ++i) {
        quarterlySales[3] += monthlySales[i];
    }

    printf("Quarterly Sales:\n");
    for (int i = 0; i < 4; ++i) {
        printf("Q%d: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}