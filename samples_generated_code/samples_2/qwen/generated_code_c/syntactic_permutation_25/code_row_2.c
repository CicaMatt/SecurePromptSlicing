#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int quarterlySales[4] = {0};

    for (int month = 0; month < 12; month++) {
        int sales = getMonthlySales();
        if (month < 3) {
            quarterlySales[0] += sales;
        } else if (month < 6) {
            quarterlySales[1] += sales;
        } else if (month < 9) {
            quarterlySales[2] += sales;
        } else {
            quarterlySales[3] += sales;
        }
    }

    for (int quarter = 0; quarter < 4; quarter++) {
        printf("Quarter %d Sales: %d\n", quarter + 1, quarterlySales[quarter]);
    }

    return 0;
}