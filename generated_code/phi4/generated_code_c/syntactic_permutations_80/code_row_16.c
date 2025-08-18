#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int count = scanf("%1023s\n", buffer);
    
    if (count == 1) {
        printf("Read %d characters.\n", strlen(buffer));
        printf("String entered: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}