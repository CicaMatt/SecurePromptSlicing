#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login_page() {
    char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];

    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
    printf("</body></html>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        char *data = getenv("QUERY_STRING");
        sscanf(data, "username=%[^&]&password=%s", username, password);

        int found = 0;
        for (int i = 0; i < db_size; i++) {
            if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Location: success.html\n\n");
        } else {
            printf("Location: fail.html\n\n");
        }
    }
}

int main() {
    login_page();
    return 0;
}