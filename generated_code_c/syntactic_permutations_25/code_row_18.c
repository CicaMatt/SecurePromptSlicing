#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getMonthlySales(){
    srand(time(NULL));
    int sales = rand()%10000;
    return sales;
}
int main(){
    printf("Month  Sales\n");
    for(int month=1;month<=12;month++){
        int sales = getMonthlySales();
        printf("%d   %d\n",month,sales);
    }
    return 0;
}