#include <stdio.h>
    int main() {
        int sum = 0;
        int i;
        for (i = 0; i <= 2; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }