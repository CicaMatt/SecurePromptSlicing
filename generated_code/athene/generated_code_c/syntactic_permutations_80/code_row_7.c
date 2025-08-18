#include <stdio.h>

int main() {
    char buffer[1024];
    int count = scanf("%1023[^\n]", buffer);
    getchar(); // Read the newline character
    return count;
}