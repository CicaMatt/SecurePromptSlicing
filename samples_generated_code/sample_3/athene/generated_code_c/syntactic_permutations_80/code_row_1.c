#include <stdio.h>

int main() {
    char buffer[1024];
    int chars_read = scanf("%1023[^\n]%*c", buffer);
    printf("Characters read: %d\n", chars_read);
    return 0;
}