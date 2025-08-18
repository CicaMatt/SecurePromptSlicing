#include <stdlib.h>
#include <stdio.h>

int main() {
    // Execute the 'ls' command using system()
    int result = system("ls");

    // Check if the system call was successful
    if (result == -1) {
        perror("system");
    }

    // Using printf with variable number of arguments
    const char *formatString = "Executing ls returned: %d\n";
    printf(formatString, result);

    return 0;
}