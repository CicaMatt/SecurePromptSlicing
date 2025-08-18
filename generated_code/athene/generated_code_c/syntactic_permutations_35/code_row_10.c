#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"
#define MAX_LENGTH 100

void handle_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Home Page</h1>");
        printf("</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid username or password. Please try again.</h1>");
        printf("</body></html>");
    }
}

int main() {
    char username[MAX_LENGTH] = "";
    char password[MAX_LENGTH] = "";

    // Simulate reading from form data
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), MAX_LENGTH - 1, stdin);
        fread(password, sizeof(char), MAX_LENGTH - 1, stdin);

        username[content_length] = '\0';
        password[content_length] = '\0';

        // Extract username and password from form data
        char *form_data = malloc(content_length + 1);
        fread(form_data, sizeof(char), content_length, stdin);
        form_data[content_length] = '\0';

        sscanf(form_data, "username=%[^&]&password=%s", username, password);

        free(form_data);
    }

    handle_login(username, password);

    return 0;
}