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
        if (i % 3 == 2) { // Complete a quarter
            quarterlySales[i / 3] += monthlySales[i];
            quarterlySales[(i + 1) / 3] += monthlySales[i]; // Add the first month of the next quarter as well
        } else {
            quarterlySales[i / 3] += monthlySales[i];
        }
    }

    for (int i = 0; i < 4; ++i) {
        printf("Quarter %d Sales: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}