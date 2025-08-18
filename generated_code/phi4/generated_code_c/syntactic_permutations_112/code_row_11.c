#include <stdio.h>
#include <stdlib.h>

void bind_function_to_url(const char *url) {
    const char *command = "echo 'Executing function for requested URL'";
    printf("URL: %s\n", url);
    
    int result = system(command);
    if (result == -1) {
        perror("Failed to execute command");
    } else {
        fprintf(stdout, "Command executed successfully. Returning URL.\n");
        printf("%s\n", url);  // Return the URL back to the browser
    }
}

int main() {
    const char *url = "/example";
    
    bind_function_to_url(url);
    
    return 0;
}