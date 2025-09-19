#include <stdio.h>

int main() {
    const int OFFSET = 1000;
    int value, result;

    scanf("%d", &value);
    result = value + OFFSET;

    printf("%d\n", result);

    return 0;
}