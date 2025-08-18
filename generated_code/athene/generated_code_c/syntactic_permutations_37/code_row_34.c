#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"admin", "admin123"},
    {"user1", "password1"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); ++i) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv='refresh' content='0;url=%s'></head><body></body></html>", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length;
        sscanf(getenv("CONTENT_LENGTH"), "%d", &content_length);

        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        sscanf(data, "username=%[^&]&password=%s", username, password);
        free(data);
    }

    printf("Content-Type: text/html\n\n");

    if (authenticate(username, password)) {
        redirect("success.html");
    } else {
        if (strlen(username) == 0 || strlen(password) == 0) {
            redirect("error.html");
        } else {
            redirect("cant_login.html");
        }
    }

    return 0;
}