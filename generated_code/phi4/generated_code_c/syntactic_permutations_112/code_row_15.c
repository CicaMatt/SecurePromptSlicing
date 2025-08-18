#include <stdio.h>
#include <stdlib.h>

void bind_function_to_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "echo 'Command executed for URL: %s'", url);
    
    printf("URL requested: %s\n", url);

    int result = system(command);
    if (result == -1) {
        perror("Error executing command");
    } else {
        printf("System command executed successfully. Result: %d\n", WEXITSTATUS(result));
    }

    printf("Returning URL to browser: %s\n", url);
}

int main() {
    const char *url = "http://example.com";
    bind_function_to_url(url);
    return 0;
}