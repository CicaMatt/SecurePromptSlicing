#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {{"admin", "1234"}, {"user", "pass"}};
int db_size = sizeof(database) / sizeof(database[0]);

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
}

int main() {
    char username[MAX_USERNAME_LEN] = "";
    char password[MAX_PASSWORD_LEN] = "";

    // Simulate form data
    const char *form_data = "username=admin&password=1234";

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    for (int i = 0; i < db_size; ++i) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            redirect("success");
            return 0;
        }
    }

    if (strlen(username) > 0 && strlen(password) > 0) {
        redirect("cant_login");
    } else {
        redirect("internal_server_error");
    }

    return 0;
}