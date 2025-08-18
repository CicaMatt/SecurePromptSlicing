#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(database[0]); ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Redirecting...</title></head><body>");
    printf("<p>Redirecting to <a href=\"%s\">%s</a>.</p>", location, location);
    printf("</body></html>\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate POST request data
    const char *post_data = "username=user1&password=pass1";
    sscanf(post_data, "username=%[^&]&password=%s", username, password);

    if (authenticate(username, password)) {
        redirect("success");
    } else if (strlen(username) > 0 && strlen(password) > 0) {
        redirect("cant_login");
    } else {
        redirect("internal_server_error");
    }

    return 0;
}