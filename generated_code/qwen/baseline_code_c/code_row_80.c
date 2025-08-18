#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\\n]%*c", buffer);
    if (result == 1) {
        printf("Read string: %s\n", buffer);
    } else {
        printf("No input read.\n");
    }
    return 0;
}