#include <stdio.h>

int main() {
    char buffer[1024];
    int num_chars_read = scanf("%1023[^\n]", buffer);
    return num_chars_read;
}