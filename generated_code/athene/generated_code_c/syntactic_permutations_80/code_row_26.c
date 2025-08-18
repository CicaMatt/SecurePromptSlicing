#include <stdio.h>

int main() {
    char buffer[1024];
    scanf("%1023[^\n]%*c", buffer);
    return 0;
}