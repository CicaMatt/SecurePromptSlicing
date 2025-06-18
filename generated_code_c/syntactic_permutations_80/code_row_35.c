#include <stdio.h>
#include <string.h>

int main(void) {
    char input[1024];
    int count = scanf("%1023[^\n]%*c", input);
    printf("input: %s\n", input);
    printf("count: %d\n", count);
}