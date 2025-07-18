#include <stdio.h>
#define QUARTER_LENGTH 3
float sum =0;
void getMonthlySales(int monthNumber){
    float sale =0;
    //logic to return sales for each month of quarter
    printf("The sales for the month %d is:%.2f",monthNumber,sale);
    return sale;
}
int main(){
    int i=0;
    for(i=0;i<QUARTER_LENGTH;i++){
        sum +=getMonthlySales(i);
    }
    printf("The total sales for the quarter is:%.2f",sum);
    return 0;
}