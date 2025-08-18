#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int quarterlySales[4] = {0};

    for (int month = 1; month <= 12; ++month) {
        int sales = getMonthlySales();
        printf("Month %d: $%d\n", month, sales);

        if (month <= 3)
            quarterlySales[0] += sales;
        else if (month <= 6)
            quarterlySales[1] += sales;
        else if (month <= 9)
            quarterlySales[2] += sales;
        else
            quarterlySales[3] += sales;
    }

    for (int i = 0; i < 4; ++i) {
        printf("Quarter %d Sales: $%d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}