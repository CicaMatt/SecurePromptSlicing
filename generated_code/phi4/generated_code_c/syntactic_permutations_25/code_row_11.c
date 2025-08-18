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
        printf("Month %d Sales: %d\n", month, sales);
        
        // Determine which quarter the current month belongs to
        int quarterIndex = (month - 1) / 3;
        quarterlySales[quarterIndex] += sales;
    }

    for (int q = 0; q < 4; ++q) {
        printf("Quarter %d Total Sales: %d\n", q + 1, quarterlySales[q]);
    }

    return 0;
}