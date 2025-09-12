#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (!file) {
        perror("Error opening template file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    
    fclose(file);
}

void hello(const char *username) {
    const char *template_file = "hello.html";
    render_template(template_file, username);
    printf("Hello, %s!\n", username);
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username_start = url + 7;
        hello(username_start);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char simulated_url[] = "/hello/JohnDoe";
    handle_request(simulated_url);

    return 0;
}