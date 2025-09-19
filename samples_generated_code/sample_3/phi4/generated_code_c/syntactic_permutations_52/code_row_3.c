#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

// Simple session management using global variable
char *session_username = NULL;

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

void do_login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session_username = username;
        redirect("/secret");
    } else {
        printf("Login failed. Invalid username or password.\n");
    }
}

void show_index_page() {
    printf("<html><body>\n"
           "<h1>Welcome to the Index Page</h1>\n"
           "<a href='/login'>Login</a>\n"
           "</body></html>\n");
}

void show_login_page() {
    printf("<html><body>\n"
           "<h1>Login Page</h1>\n"
           "<form action='/do_login' method='post'>\n"
           "  Username: <input type='text' name='username'><br>\n"
           "  Password: <input type='password' name='password'><br>\n"
           "  <input type='submit' value='Login'>\n"
           "</form>\n"
           "</body></html>\n");
}

void show_secret_page() {
    printf("<html><body>\n"
           "<h1>Secret settings</h1>\n"
           "%s\n", session_username ? "Welcome, authorized user." : "Unauthorized access.");
    printf("</body></html>\n");
}

int main() {
    char url[100] = "/";

    // Simulate a web server request handling
    if (strcmp(url, "/") == 0) {
        show_index_page();
    } else if (strcmp(url, "/login") == 0) {
        show_login_page();
    } else if (strcmp(url, "/do_login?username=admin&password=password") == 0) { // Simulating login form submission
        do_login("admin", "password");
    } else if (strcmp(url, "/secret") == 0) {
        show_secret_page();
    }

    return 0;
}