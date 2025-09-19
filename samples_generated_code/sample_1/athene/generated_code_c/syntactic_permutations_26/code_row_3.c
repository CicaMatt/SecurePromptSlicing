#include <stdio.h>

int get_sales(int month) {
    int sales[] = {15000, 23000, 18000};
    return sales[month];
}

int main() {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += get_sales(i);
    }
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}