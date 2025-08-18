#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(0));
    int quarterlySales[4] = {0};

    for (int i = 0; i < 12; i++) {
        int sales = getMonthlySales();
        quarterlySales[i / 3] += sales;
    }

    printf("Quarterly Sales:\n");
    for (int i = 0; i < 4; i++) {
        printf("Q%d: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}