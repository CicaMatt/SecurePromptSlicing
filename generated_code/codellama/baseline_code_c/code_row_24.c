#include<stdio.h>
int main() {
    int random1 = (rand() % 990) + 10;
    int random2 = (rand() % 990) + 10;
    printf("%d - %d = %d", random1, random2, random1 - random2);
    return 0;
}