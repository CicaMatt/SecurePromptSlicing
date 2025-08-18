#include <stdio.h>

int main() {
    char buffer[1024];
    int count = scanf("%1023s", buffer);
    return count;
}