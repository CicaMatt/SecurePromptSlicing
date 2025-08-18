#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    char username[100], password[100];
    
    // Simulate receiving form data (for simplicity, using fgets)
    printf("Content-Type: text/html\n\n");
    printf("<form method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");

    // Simulate POST request (for simplicity, using stdin)
    if (fgets(username, sizeof(username), stdin) && fgets(password, sizeof(password), stdin)) {
        username[strcspn(username, "\n")] = 0; // Remove newline
        password[strcspn(password, "\n")] = 0; // Remove newline

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            redirect("success.html");
        } else {
            redirect("cant_login.html");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<p>An error occurred while processing your request.</p>");
    }

    return 0;
}