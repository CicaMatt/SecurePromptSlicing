#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\\n]%*c", buffer);
    if (result == 1) {
        printf("Read string: %s\n", buffer);
    } else {
        printf("No valid input was found.\n");
    }
    return 0;
}