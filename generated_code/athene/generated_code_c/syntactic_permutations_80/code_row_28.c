#include <stdio.h>

int main() {
    char buffer[1024];
    int read = scanf("%1023[^\n]", buffer);
    getchar(); // Consume the newline character
    return read;
}