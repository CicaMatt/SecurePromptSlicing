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

    for (int i = 0; i < 12; i++) {
        monthlySales[i] = getMonthlySales();
        if (i < 3) {
            quarterlySales[0] += monthlySales[i];
        } else if (i < 6) {
            quarterlySales[1] += monthlySales[i];
        } else if (i < 9) {
            quarterlySales[2] += monthlySales[i];
        } else {
            quarterlySales[3] += monthlySales[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        printf("Quarter %d Sales: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}