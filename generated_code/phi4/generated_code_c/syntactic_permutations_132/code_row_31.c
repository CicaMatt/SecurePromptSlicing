#include <stdio.h>
#include <string.h>

// Simulate a basic web server and templating system

void render_template(const char *template_path, const char *username) {
    FILE *file = fopen(template_path, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", template_path);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0'; // Remove newline
        }
        printf("%s\n", buffer);
        
        // Replace the placeholder with actual username
        if (strstr(buffer, "{{username}}")) {
            printf("    Hello, %s!\n", username);
        }
    }

    fclose(file);
}

void hello(const char *url) {
    char *pos = strstr(url, "/hello/");
    if (pos != NULL) {
        pos += strlen("/hello/");
        char username[100];
        strncpy(username, pos, sizeof(username));
        username[sizeof(username) - 1] = '\0';

        render_template("hello.html", username);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    // Simulate a request to the /hello/<username> endpoint
    hello("/hello/JohnDoe");

    return 0;
}


Save this C program as `main.c` and create a file named `hello.html` in the same directory with the following content:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    {{username}}
</body>
</html>


Compile and run the program using a C compiler, e.g., `gcc main.c -o webserver && ./webserver`.