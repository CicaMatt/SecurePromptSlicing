#include <stdio.h>
#include <string.h>

// Function declarations
void login();
int do_login(const char *username, const char *password);
void admin_page();

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<form action='do_login' method='POST'>\n");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        return 1; // Admin login successful
    }
    return 0; // Login failed
}

void admin_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>Welcome to the Admin Page</h1>\n");
    printf("</body></html>\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        const char *method = argv[1];
        
        if (strcmp(method, "GET") == 0) {
            login();
        } else if (strcmp(method, "POST") == 0 && argc > 3) {
            const char *username = argv[2];
            const char *password = argv[3];

            if (do_login(username, password)) {
                admin_page();
            } else {
                printf("Content-Type: text/html\n\n");
                printf("<html><body>\n");
                printf("<h1>Login Failed</h1>\n");
                printf("</body></html>\n");
            }
        }
    }

    return 0;
}