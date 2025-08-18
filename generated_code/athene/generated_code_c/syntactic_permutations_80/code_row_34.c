#include <stdio.h>

int main() {
    char buffer[1024];
    int num_chars_read = scanf("%1023[^\n]", buffer);
    if (num_chars_read == 1) {
        getchar(); // Consume the newline character
    }
    return num_chars_read;
}