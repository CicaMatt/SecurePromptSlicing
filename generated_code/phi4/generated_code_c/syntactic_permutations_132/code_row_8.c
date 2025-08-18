#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256

// Function to read HTML content from a file
char* read_html_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';
    
    fclose(file);
    return content;
}

// Function to render the template with username
void render_template(const char *username) {
    char *html_content = read_html_file("template.html");
    if (html_content == NULL) {
        printf("Error loading HTML file.\n");
        return;
    }

    // Replace placeholder in HTML with actual username
    size_t len = strlen(html_content);
    for (size_t i = 0; i < len; ++i) {
        if (strncmp(&html_content[i], "{{username}}", 12) == 0) {
            char buffer[MAX_USERNAME_LENGTH + 1];
            snprintf(buffer, sizeof(buffer), "%s", username);

            size_t buffer_len = strlen(buffer);
            memmove(&html_content[i], buffer, buffer_len);
            memmove(&html_content[i + buffer_len], &html_content[i + 12], len - i + 12 - buffer_len);
        }
    }

    printf("%s\n", html_content);
    free(html_content);
}

// Simulating a web server request handler
void handle_request(const char *url) {
    if (strncmp(url, "/user/", 6) == 0) {
        const char *username = url + 6;
        render_template(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a user visiting the URL /user/johndoe
    handle_request("/user/johndoe");
    
    return 0;
}