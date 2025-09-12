#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple function to simulate a web server handling URLs and rendering templates
void handle_request(const char *url) {
    const char *username = NULL;

    // Extract username from URL if it matches the pattern /hello/<username>
    if (strncmp(url, "/hello/", 7) == 0) {
        username = url + 7;
        
        // Open and read template file
        FILE *file = fopen("hello.html", "r");
        if (!file) {
            printf("Error: could not open hello.html\n");
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            // Replace the placeholder {{ username }} with actual username
            if (strstr(line, "{{ username }}") != NULL) {
                size_t placeholder_len = strlen("{{ username }}");
                snprintf(line + strlen(line) - placeholder_len, 257, "%s", username);
            }
            printf("%s", line);
        }

        fclose(file);
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}


Create a file named `hello.html` with the following content to test:


<!DOCTYPE html>
<html>
<head>
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {{ username }}!</h1>
</body>
</html>


Compile and run the C program by passing a URL like `./program /hello/JohnDoe`.