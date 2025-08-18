#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url);
char* render_template(const char* template_path, const char* username);

int main() {
    // Simulating a request to /hello/JohnDoe
    char url[] = "/hello/JohnDoe";

    printf("Handling URL: %s\n", url);
    handle_request(url);

    return 0;
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        size_t username_start = strlen("/hello/");
        char* username_end = strchr(&url[username_start], '/');
        if (!username_end) {
            username_end = &url[strlen(url)];
        }
        size_t username_length = username_end - &url[username_start];
        
        char username[username_length + 1];
        strncpy(username, &url[username_start], username_length);
        username[username_length] = '\0';

        printf("Rendered HTML:\n%s", render_template("hello.html", username));
    } else {
        printf("404 Not Found\n");
    }
}

char* render_template(const char* template_path, const char* username) {
    // Simulated file content
    const char *template_content = "<html><body>Hello, {username}!</body></html>";

    // Allocate memory for the result string
    size_t result_length = strlen(template_content) + strlen(username) - 4; // subtracting length of "{username}"
    char* result = (char*)malloc(result_length + 1);

    if (!result) {
        return "Error: Memory allocation failed";
    }

    // Replace {username} with the actual username
    snprintf(result, result_length + 1, template_content, username);

    return result;
}


This code simulates a simple web server handling request to `/hello/<username>`. It replaces `{username}` in an HTML template with the provided username. The `render_template` function simulates reading from a file by using a hardcoded string for simplicity.