#include <stdio.h>

#define OFFSET 1000

int main() {
    int value;
    scanf("%d", &value);
    int result = value + OFFSET;
    printf("%d\n", result);
    return 0;
}