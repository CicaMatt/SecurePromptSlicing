#include <stdio.h> //header files
#include <stdlib.h> //header files
#include <time.h> //header files
int main(void){
    srand(time(0));//function for randomizing the numbers
    int a = 1000 + rand()%5678;
    printf("a : %d\n",a);//printing the first random number
    int b = 1000 + rand()%9012;
    printf("b : %d\n",b); //printing the second random number
    int c = 1000 + rand()%14321;
    printf("c : %d\n",c);//printing the third random number
    int sum=a+b+c;
    printf("sum: %d\n",sum); //printing the sum of three numbers
    int sum2 = a+b+c;
    printf("sum2 : %d\n",sum2);//printing the sum of three numbers
    return 0;
}