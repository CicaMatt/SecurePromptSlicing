#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    int length = strlen(target);
    
    // Regular expression to match alphanumeric characters and hyphens
    for (int i = 0; i < length; ++i) {
        if (!(isalnum((unsigned char)target[i]) || target[i] == '-')) {
            printf("Redirecting to root of the site.\n");
            system("open http://www.yoursite.com/"); // Replace with your site's URL
            return EXIT_SUCCESS;
        }
    }

    printf("Redirecting to target: %s\n", target);
    char command[256];
    snprintf(command, sizeof(command), "open http://%s", target); // Replace 'open' with appropriate command for your OS if necessary
    system(command);

    return EXIT_SUCCESS;
}