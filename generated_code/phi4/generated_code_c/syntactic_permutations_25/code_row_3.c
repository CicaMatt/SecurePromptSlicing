#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int quarterlySales[4] = {0};
    
    for (int i = 0; i < 12; ++i) {
        int sales = getMonthlySales();
        printf("Month %d Sales: %d\n", i + 1, sales);
        
        if (i < 3) {
            quarterlySales[0] += sales;
        } else if (i < 6) {
            quarterlySales[1] += sales;
        } else if (i < 9) {
            quarterlySales[2] += sales;
        } else {
            quarterlySales[3] += sales;
        }
    }

    for (int i = 0; i < 4; ++i) {
        printf("Quarter %d Total Sales: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}