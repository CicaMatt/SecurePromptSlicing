#include <stdio.h>

int main() {
    char buffer[1024];
    int n = scanf("%1023[^\n]", buffer);
    return n;
}