#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales(){
    int result = 0;
    srand(time(NULL));
    result = rand() % 100000;
    return result;
}

void main(){
    int i, firstQuarterSum=0, secondQuarterSum=0, thirdQuarterSum=0, fourthQuarterSum=0;
    for(i=0; i<12; i++){
        if (i<=3){
            firstQuarterSum += getMonthlySales();
        } else if (i>3 && i<=6){
            secondQuarterSum += getMonthlySales();
        } else if (i>6 && i<=9){
            thirdQuarterSum += getMonthlySales();
        } else {
            fourthQuarterSum += getMonthlySales();
        }
    }
    printf("First Quarter Sum: %d\n", firstQuarterSum);
    printf("Second Quarter Sum: %d\n", secondQuarterSum);
    printf("Third Quarter Sum: %d\n", thirdQuarterSum);
    printf("Fourth Quarter Sum: %d\n", fourthQuarterSum);
}