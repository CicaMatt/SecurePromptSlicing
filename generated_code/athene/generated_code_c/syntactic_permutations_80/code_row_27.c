#include <stdio.h>

int main() {
    char buffer[100];
    int result = scanf("%99[^\n]", buffer);
    return result;
}