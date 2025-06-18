#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/types.h>

    int main(int argc, char** argv) {
        // Create a web app.
        system("mkdir mywebapp");
        chdir("mywebapp");

        // Create a route called /api.
        system("mkdir api");
        chdir("api");

        // Get the payload parameter from the URL.
        char* url = getenv("REQUEST_URI");
        int pos = strstr(url, "?payload=") - url;
        if (pos < 0) {
            printf("Error: Invalid request.\n");
            return EXIT_FAILURE;
        }

        // Load the payload.
        char* filename = &url[pos + strlen("?payload=")];
        int fd = open(filename, O_RDONLY);
        if (fd < 0) {
            printf("Error: Payload not found.\n");
            return EXIT_FAILURE;
        }

        // Return the name value from the dictionary.
        char* content = malloc(1024);
        read(fd, content, 1024);
        close(fd);
        printf("Content-Type: application/json\n");
        printf("\n");
        printf("%s", content);

        free(content);
        return EXIT_SUCCESS;
    }