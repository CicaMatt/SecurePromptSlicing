#include <stdio.h>
int main() {
    int sum = 0, i;
    for(i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    printf("Total sales for the first quarter: %d", sum);
}