#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
} RequestContext;

char* render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + strlen(username) + 1);
    fread(buffer, 1, length, file);
    fclose(file);

    char *pos = buffer;
    while ((pos = strstr(pos, "{{username}}")) != NULL) {
        memmove(pos + strlen(username), pos + strlen("{{username}}"), strlen(pos + strlen("{{username}}")) + 1);
        memcpy(pos, username, strlen(username));
        pos += strlen(username);
    }

    return buffer;
}

void hello(RequestContext *context) {
    char *response = render_template("hello.html", context->username);
    printf("%s\n", response); // Simulate sending the response
    free(response);
}

// Mock decorator function to simulate URL routing
void route_to_hello(char *url, char *username) {
    if (strcmp(url, "/hello/") == 0) return; // Skip if not matching

    RequestContext context = { .username = username };
    hello(&context);
}

int main() {
    char url[] = "/hello/JohnDoe";
    char username[] = "JohnDoe";
    route_to_hello(url, username);

    return 0;
}