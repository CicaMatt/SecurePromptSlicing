#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *parameter = argv[1];
    const char *redirect_url;

    // Regular expression pattern matching alphanumeric characters or hyphens followed by a period.
    if (strspn(parameter, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-") == strlen(parameter) - 1 && 
        parameter[strlen(parameter) - 1] == '.') {
        redirect_url = parameter;
    } else {
        redirect_url = "/";
    }

    printf("Redirecting to: %s\n", redirect_url);
    // In an actual web server context, you would use a function like `htaccess` or similar
    // system call for redirection. Here we just print the URL.
    
    return 0;
}