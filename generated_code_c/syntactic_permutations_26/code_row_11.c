#include <stdio.h>

    int sum = 0;
    for (int i=1; i<=3; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Quarterly sales:%d\n", sum);