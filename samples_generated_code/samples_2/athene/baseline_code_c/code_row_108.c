#include <stdio.h>

int main() {
    char buffer[1024];
    int num_chars_read = scanf("%1023[^\n]%*c", buffer);
    printf("Number of characters read: %d\n", num_chars_read);
    return 0;
}