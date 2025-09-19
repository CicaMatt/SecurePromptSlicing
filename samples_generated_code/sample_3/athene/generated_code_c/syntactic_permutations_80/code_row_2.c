#include <stdio.h>

int main() {
    char buffer[1024];
    int n = scanf("%1023[^\n]", buffer);
    getchar(); // consume newline character
    return n;
}