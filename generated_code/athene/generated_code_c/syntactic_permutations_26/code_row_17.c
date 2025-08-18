#include <stdio.h>

int getSales(int month) {
    int sales[] = {1500, 1800, 2200};
    return sales[month];
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getSales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}