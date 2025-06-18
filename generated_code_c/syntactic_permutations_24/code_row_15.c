#include<stdio.h>
    #include<stdlib.h>
    #include<time.h>

    int main(){
        srand(time(NULL));
        int number1= (rand()%900)+10;
        int number2= (rand()%900)+10;
        printf("The random numbers are %d and %d\n",number1,number2);
        int result=number1-number2;
        printf("Difference is %d",result);
    }