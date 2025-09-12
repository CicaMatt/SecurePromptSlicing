#include <stdio.h>

int scan(char *buffer, size_t max_size) {
    if (max_size == 0 || buffer == NULL) return -1;

    int count = scanf("%1023[^\n]%*c", buffer);
    return count > 0 ? count : 0;
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int num_chars = scan(buffer, sizeof(buffer));

    if (num_chars > 0) {
        printf("You entered: %s\n", buffer);
        printf("Number of characters read: %d\n", num_chars - 1); // Excluding newline
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}