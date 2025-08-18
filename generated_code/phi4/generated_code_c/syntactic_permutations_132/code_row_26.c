#include <stdio.h>
#include <string.h>

// Simple HTTP server simulation for demonstration purposes

void render_template(const char* template_file, const char* username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", template_file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }
        printf("%s\n", line);
    }

    // Close the template file
    fclose(file);

    // Print the username in place of {{username}}
    printf("Hello, %s!\n", username);
}

void hello(const char* path) {
    if (strncmp(path, "/hello/", 7) == 0) {
        const char *username = path + 7;
        render_template("hello.html", username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate visiting /hello/<username>
    hello("/hello/JohnDoe");

    return 0;
}


To run this code, ensure you have a file named `hello.html` in the same directory with some HTML content. The script will replace the placeholder `{{username}}` with the actual username extracted from the URL path.