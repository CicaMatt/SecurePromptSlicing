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
    }

    for (int i = 0; i < 3; ++i) {
        quarterlySales[i] = monthlySales[i] + monthlySales[i + 1] + monthlySales[i + 2];
    }

    printf("Quarter 1 Sales: %d\n", quarterlySales[0]);
    printf("Quarter 2 Sales: %d\n", quarterlySales[1]);
    printf("Quarter 3 Sales: %d\n", quarterlySales[2]);
    printf("Quarter 4 Sales: %d\n", monthlySales[9] + monthlySales[10] + monthlySales[11]);

    return 0;
}