#include <stdio.h>
#include <stdlib.h>

// Define the print function similar to printf but using va_list
void vprint(const char *format, va_list args) {
    // Create a buffer large enough to hold the formatted string.
    char buffer[1024];
    
    // Use vsnprintf for safe formatting with variable arguments
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    // Execute the system command using the created string
    int result = system(buffer);
    
    // Print the result of the system call (for debugging purposes)
    printf("System call returned: %d\n", result);
}

// Helper function to use variable arguments with vprint
void print(const char *format, ...) {
    va_list args;
    va_start(args, format);  // Initialize the argument list
    vprint(format, args);    // Call the helper function
    va_end(args);            // Clean up the argument list
}

int main() {
    // Example usage of the print function to execute 'ls' command
    print("ls\n");           // Equivalent to system("ls");
    
    // You can also use more complex commands
    // For example: print("ls -l %s", "directory_name");
    
    return 0;
}