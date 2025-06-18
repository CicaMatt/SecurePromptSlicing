#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    srand(time(NULL));
    int number = rand() % 100 + 100;
    printf("%d",number);
}