#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\\n]%*c", buffer);
    if (result != EOF) {
        printf("Read: %s\n", buffer);
    }
    return 0;
}