#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful. Redirecting to secret page...\n");
        // Simulate setting the username in session
        printf("Session set: Username = %s\n", username);
        // Simulate redirect to secret page
        index_secret();
    } else {
        printf("Invalid username or password.\n");
    }
}

void index_page() {
    printf("<html>\n");
    printf("<head><title>Login Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Index Page</h1>\n");
    printf("<p><a href=\"/login\">Login here</a></p>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void index_secret() {
    printf("<html>\n");
    printf("<head><title>Secret Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Secret settings</h1>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate user input for login
    const char *username = "admin";
    const char *password = "password123";

    index_page();
    do_login(username, password);

    return 0;
}