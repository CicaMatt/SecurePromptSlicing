#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} Context;

void render_template(char *template, Context *context) {
    FILE *file = fopen("hello.html", "r");
    if (!file) {
        perror("Failed to open template file");
        exit(1);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos;
        if ((pos = strstr(buffer, "{{username}}") - buffer) != (size_t)-1) {
            printf("%.*s", (int)pos, buffer);
            printf("%s", context->username);
            pos += 10; // Length of "{{username}}"
            printf("%s", &buffer[pos]);
        } else {
            printf("%s", buffer);
        }
    }
    fclose(file);
}

typedef void (*Handler)(Context*);

void bind_to_url(const char *url, Handler handler) {
    Context context;
    char username[100];
    printf("Enter username: ");
    scanf("%99s", username); // Simulate user input for the URL /hello/<username>
    context.username = strdup(username);
    handler(&context);
}

void hello_world_handler(Context *context) {
    render_template("hello.html", context);
}

int main() {
    bind_to_url("/hello/<username>", hello_world_handler);
    return 0;
}