#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Minimal web server simulation with URL routing and templating

void render_template(const char* template_path, const char* username) {
    FILE *file = fopen(template_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the contents of the template file
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);
    buffer[fsize] = '\0';

    // Replace placeholder with username
    const char* placeholder = "<username>";
    size_t len_placeholder = strlen(placeholder);
    char* pos;
    while ((pos = strstr(buffer, placeholder)) != NULL) {
        memmove(pos + strlen(username), pos + len_placeholder, fsize - (pos - buffer + len_placeholder));
        memcpy(pos, username, strlen(username));
        fsize -= len_placeholder - strlen(username);
    }

    // Output the rendered template
    printf("%s\n", buffer);

    free(buffer);
}

void hello_function(const char* url) {
    const char *username = NULL;
    if (strncmp(url, "/hello/", 7) == 0) {
        username = url + 7; // Extract username part from URL
    }

    if (username != NULL && strlen(username) > 0) {
        render_template("hello.html", username);
    } else {
        printf("Hello, world!\n"); // Default response
    }
}

int main() {
    // Simulate visiting the URL /hello/JohnDoe
    hello_function("/hello/JohnDoe");
    
    return 0;
}
