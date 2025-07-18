#include <stdio.h>
#include <stdlib.h>

int main(){
    char buffer[1024];
    int num;
    printf("Enter your name: ");
    scanf("%s\n", buffer);
    printf("Hello %s!\n", buffer);
    return 0;
}