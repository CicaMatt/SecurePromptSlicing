#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
   srand(time(0));
   int num = rand() % 1000;
   printf("The number is : %d\n",num);
}