#include <stdio.h>

int getSales(int month) {
    // Example function that returns sales for a given month
    // In a real scenario, this could fetch data from a database or another source
    int sales[] = {15000, 20000, 25000};
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