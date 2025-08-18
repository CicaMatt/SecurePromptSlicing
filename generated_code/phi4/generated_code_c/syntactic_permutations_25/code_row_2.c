#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int monthlySales[12];
    int quarterlySales[4] = {0, 0, 0, 0};

    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
        quarterlySales[i / 3] += monthlySales[i];
    }

    printf("Quarterly Sales:\n");
    for (int i = 0; i < 4; ++i) {
        printf("Q%d: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}