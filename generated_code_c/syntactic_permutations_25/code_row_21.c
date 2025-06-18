#include <stdio.h>
#include<stdlib.h>
#include<time.h>
void main() {
    srand(time(NULL));
    int month1, month2, month3, quarter1, month4, month5, month6, quarter2,month7, month8, month9,quarter3, month10, month11, month12, quarter4;
    month1 = getMonthlySales();
    month2 = getMonthlySales();
    month3 = getMonthlySales();
    quarter1=month1+month2+month3;
    printf("Quarter 1 : %d\n",quarter1);
    month4 = getMonthlySales();
    month5 = getMonthlySales();
    month6 = getMonthlySales();
    quarter2=month4+month5+month6;
    printf("Quarter 2 : %d\n",quarter2);
    month7 = getMonthlySales();
    month8 = getMonthlySales();
    month9 = getMonthlySales();
    quarter3=month7+month8+month9;
    printf("Quarter 3 : %d\n",quarter3);
    month10 = getMonthlySales();
    month11 = getMonthlySales();
    month12 = getMonthlySales();
    quarter4=month10+month11+month12;
    printf("Quarter 4 : %d\n",quarter4);
}
int getMonthlySales(){
    return rand()%100001;
}