#include <stdio.h>
#include <string.h>

void render_template(const char *template_path, const char *username) {
    // Simulated rendering logic for demonstration purposes.
    printf("Rendering template: %s with username: %s\n", template_path, username);
}

int handle_request(const char *request_url) {
    if (strcmp(request_url, "/hello/") == 0) {
        return 1; // URL matches /hello/
    } else if (strncmp(request_url, "/hello/", 7) == 0) {
        const char *username = request_url + 7;
        render_template("hello.html", username);
        return 2; // URL matches /hello/<username>
    }
    return 0; // No match
}

void hello(const char *username) {
    printf("Hello, %s!\n", username);
}

int main() {
    const char *urls[] = {"/", "/hello/", "/hello/JohnDoe", "/about"};
    int num_urls = sizeof(urls) / sizeof(urls[0]);

    for (int i = 0; i < num_urls; ++i) {
        printf("Processing URL: %s\n", urls[i]);
        switch (handle_request(urls[i])) {
            case 1:
                hello(""); // No username provided
                break;
            case 2:
                hello(urls[i] + 7); // Extract and pass the username
                break;
            default:
                printf("404 Not Found\n");
                break;
        }
    }

    return 0;
}