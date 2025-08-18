#include <stdio.h>
#include <string.h>

// Simulated web server functions
void send_redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

void send_response(const char *content) {
    printf("%s\n", content);
}

// Login page function (GET request)
void login_function() {
    const char *login_page = 
        "<html>\n"
        "<body>\n"
        "<form action=\"/do_login\" method=\"post\">\n"
        "Username: <input type=\"text\" name=\"username\"><br>\n"
        "Password: <input type=\"password\" name=\"password\"><br>\n"
        "<input type=\"submit\" value=\"Login\">\n"
        "</form>\n"
        "</body>\n"
        "</html>";
    send_response(login_page);
}

// Do login function (POST request)
void do_login_function(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        send_redirect("/admin_page");
    } else {
        const char *error_message = "<html><body><p>Invalid username or password.</p></body></html>";
        send_response(error_message);
    }
}

// Simulated main function to demonstrate usage
int main() {
    // Example GET request to login page
    printf("Simulating GET /login\n");
    login_function();

    // Example POST request with credentials
    printf("\nSimulating POST /do_login with username=admin and password=adminpass\n");
    do_login_function("admin", "adminpass");

    // Example POST request with incorrect credentials
    printf("\nSimulating POST /do_login with username=user and password=wrongpass\n");
    do_login_function("user", "wrongpass");

    return 0;
}