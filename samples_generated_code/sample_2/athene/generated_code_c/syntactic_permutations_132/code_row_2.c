#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} RequestContext;

void render_template(char *template_file, char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) {
        perror("Failed to open template file");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos;
        if ((pos = strstr(buffer, "{{username}}") - buffer) != 0) {
            printf("%.*s", (int)pos, buffer);
            printf("%s", username);
            pos += strlen("{{username}}");
            printf("%s", buffer + pos);
        } else {
            printf("%s", buffer);
        }
    }
    fclose(file);
}

void user_profile(RequestContext *context) {
    render_template("profile.html", context->username);
}

void route_request(char *url, void (*handler)(RequestContext *)) {
    RequestContext request;
    request.username = url + 1; // Assuming URL is in the format "/<username>"
    handler(&request);
}

int main() {
    char url[] = "/john_doe";
    route_request(url, user_profile);
    return 0;
}