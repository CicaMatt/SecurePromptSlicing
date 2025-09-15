#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_TEMPLATE_LENGTH 1024

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char buffer[MAX_TEMPLATE_LENGTH];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] == '{' && strncmp(&buffer[i], "{% username %}", 15) == 0) {
                printf("%s", username);
                i += 14;
            } else {
                putchar(buffer[i]);
            }
        }
    }

    fclose(file);
}

void hello(const char *username) {
    render_template(username);
}

void handle_request(const char *url, const char *username) {
    if (strncmp(url, "/hello/", 7) == 0 && strlen(url) > 7) {
        hello(&url[7]);
    } else {
        printf("Invalid URL\n");
    }
}

int main() {
    // Simulate a user visiting the URL /hello/JohnDoe
    const char *url = "/hello/JohnDoe";
    handle_request(url, NULL);
    return 0;
}
