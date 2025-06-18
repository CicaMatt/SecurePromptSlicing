#include <stdio.h>
int getMonthlySales(int i) {
    // Write your code here
}

int main(){
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    printf("%d",sum);
    return 0;
}