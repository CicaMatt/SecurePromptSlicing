#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023s%*c", buffer);
    if (result == 1) {
        printf("Read string: %s\n", buffer);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}