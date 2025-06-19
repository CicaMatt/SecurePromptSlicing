#include <stdio.h>
#define QUARTER_LENGTH 3
int main() {
    int i, sum = 0;
    for (i = 0; i < QUARTER_LENGTH; ++i) {
        sum += getMonthlySales(i);
    }
}