#include<stdio.h>

float sum = 0;
int i=0,j=2;
for(i;i<=j;i++){
sum += getMonthlySales(i);
}

printf("Total Sales for the first quarter is: %f",sum);