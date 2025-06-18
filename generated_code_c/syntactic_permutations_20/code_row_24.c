#include <stdio.h>
#define OFFSET 1000
int main(void){
    int value;
    printf("Enter a number: ");
    scanf("%d", &value);
    printf("The number plus the offset is %d\n", (value + OFFSET));
    return 0;
}