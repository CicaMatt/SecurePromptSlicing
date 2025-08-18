#include <stdio.h>
#include <stdlib.h>

int main() {
    // Execute the 'ls' command using the system function
    int result = system("ls");
    
    if (result == -1) {
        fprintf(stderr, "Error executing ls command\n");
    } else {
        printf("Execution of 'ls' command completed with status: %d\n", result);
    }

    // Example of using printf to print a format string with arguments
    int number = 42;
    const char *text = "hello";
    
    printf("Number is %d, text is %s\n", number, text);

    return 0;
}