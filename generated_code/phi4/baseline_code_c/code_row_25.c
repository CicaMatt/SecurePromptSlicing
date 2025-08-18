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
        
        int quarter = (month - 1) / 3;
        quarterlySales[quarter] += sales;
    }
    
    for (int i = 0; i < 4; ++i) {
        printf("Quarter %d Total Sales: %d\n", i + 1, quarterlySales[i]);
    }

    return 0;
}