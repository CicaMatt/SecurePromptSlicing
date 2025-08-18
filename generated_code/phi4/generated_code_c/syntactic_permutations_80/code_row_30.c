#include <stdio.h>

int scan(char *buffer, size_t max_length) {
    int result = 0;
    
    if (fgets(buffer, max_length, stdin) != NULL) {
        char *newline_pos = strchr(buffer, '\n');
        
        // If newline is found, replace it with a null terminator
        if (newline_pos != NULL) {
            *newline_pos = '\0';
        } else {
            // Handle case where buffer length is reached without newline
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        
        result = strlen(buffer);
    }

    return result;
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int num_read = scan(buffer, sizeof(buffer));
    printf("You entered %d characters.\n", num_read);
    printf("The input was: '%s'\n", buffer);

    return 0;
}