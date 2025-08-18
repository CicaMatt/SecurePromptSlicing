#include <stdio.h>

int main() {
    char buffer[1024];
    int count = scanf("%1023[^\n]%*c", buffer);
    printf("Characters read: %d\n", count);
    return 0;
}