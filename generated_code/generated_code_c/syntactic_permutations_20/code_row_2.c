#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    int offset = 1000;
    printf("Enter a number: ");
    int numb;
    scanf("%d", &numb);
    numb += offset;
    printf("Your number plus 1000 is %d\n", numb);
}