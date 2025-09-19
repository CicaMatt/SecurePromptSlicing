#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int sales[12];
    int quarterlySales[4] = {0};

    for (int i = 0; i < 12; ++i) {
        sales[i] = getMonthlySales();
        quarterlySales[i / 3] += sales[i];
    }

    printf("Quarter 1 Sales: %d\n", quarterlySales[0]);
    printf("Quarter 2 Sales: %d\n", quarterlySales[1]);
    printf("Quarter 3 Sales: %d\n", quarterlySales[2]);
    printf("Quarter 4 Sales: %d\n", quarterlySales[3]);

    return 0;
}