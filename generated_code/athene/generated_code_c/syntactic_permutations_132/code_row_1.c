#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define TEMPLATE_FILE "hello.html"

void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        printf("Template file not found\n");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos = 0;
        while ((pos = strstr(buffer + pos, "{{username}}")) != NULL) {
            memmove(pos, pos + strlen("{{username}}"), strlen(pos + strlen("{{username}}")) + 1);
            strncpy(pos, username, MAX_USERNAME_LENGTH);
            pos += strlen(username);
        }
        printf("%s", buffer);
    }
    fclose(file);
}

void hello(const char *username) {
    render_template(TEMPLATE_FILE, username);
}

int main() {
    const char *username = "JohnDoe";
    hello(username); // Simulate a user visiting /hello/JohnDoe
    return 0;
}