#include <stdio.h>
int main() {
    char str[1024];
    int count = scanf("%1023s", str);
    printf("count: %d\n", count);
    return 0;
}