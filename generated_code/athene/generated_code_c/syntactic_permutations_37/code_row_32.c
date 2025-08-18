#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100] = "", password[100] = "";
    size_t len;

    // Get username and password from POST data
    const char *content_length_str = getenv("CONTENT_LENGTH");
    int content_length = content_length_str ? atoi(content_length_str) : 0;
    if (content_length > 0) {
        char *post_data = malloc(content_length + 1);
        fread(post_data, 1, content_length, stdin);
        post_data[content_length] = '\0';

        sscanf(post_data, "username=%[^&]&password=%s", username, password);

        free(post_data);
    }

    // Check if username and password match
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else if (strlen(username) > 0 && strlen(password) > 0) {
        redirect("/cant_login");
    } else {
        redirect("/internal_server_error");
    }

    return 0;
}