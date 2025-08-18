#include <stdio.h>

int scan(char *buffer) {
    int count = scanf("%1022[^\n]%*c", buffer);
    return count;
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int result = scan(buffer);

    if (result > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("An error occurred during input.\n");
    }

    return 0;
}