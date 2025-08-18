#include <stdio.h>

int getSales(int month) {
    int sales[] = {1500, 2000, 1800};
    return sales[month];
}

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; i++) {
        sum += getSales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}