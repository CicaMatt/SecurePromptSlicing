#include <stdio.h>
#define OFFSET 10
int main(void) {
    int input;
    scanf("%d", &input);
    printf("The offset value is %d\n", input + OFFSET);
}