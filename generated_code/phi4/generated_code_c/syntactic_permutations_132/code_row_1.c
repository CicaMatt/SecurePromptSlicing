#include <stdio.h>
#include <string.h>

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Replace placeholder with username
        const char *placeholder = "<username>";
        size_t placeholder_len = strlen(placeholder);
        
        if (strncmp(buffer, placeholder, placeholder_len) == 0) {
            printf("%s", username);
        } else {
            fputs(buffer, stdout);
        }
    }

    fclose(file);
}

void hello(const char *url) {
    if (strncmp(url, "/hello/", 7) != 0) {
        printf("404 Not Found\n");
        return;
    }

    const char *username_start = url + 7;
    render_template(username_start);
}

int main() {
    // Example usage
    hello("/hello/JohnDoe");

    return 0;
}
