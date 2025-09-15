#include <stdio.h>
#include <string.h>

void render_hello_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (!file) {
        printf("Error: unable to open template file.\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Replace placeholder with actual username
        if (strstr(buffer, "{{username}}") != NULL) {
            size_t len = strlen(buffer);
            snprintf(buffer + (len - 10), sizeof(buffer) - (len - 10), "%s", username);
        }
        printf("%s", buffer);
    }

    fclose(file);
}

void hello(const char *username) {
    render_hello_template(username);
}

// Mock function to simulate web server behavior
void handle_request(const char *url, const char *path_info) {
    if (strcmp(url, "/hello") == 0 && strcmp(path_info, "hello/<username>") == 0) {
        // Extract username from path_info and remove the placeholder part
        const char *start = strstr(path_info, "<");
        const char *end = strstr(start, ">");
        char username[256];
        if (start && end) {
            strncpy(username, start + 1, end - start - 1);
            username[end - start - 1] = '\0';
        } else {
            strcpy(username, "Guest");
        }
        
        hello(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a user visiting the URL /hello/JohnDoe
    handle_request("/hello", "hello/<username>");

    return 0;
}
