#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<head><title>Login</title></head>\n"
           "<body>\n"
           "<form method='POST' action='/do_login'>\n"
           "Username: <input type='text' name='username'><br>\n"
           "Password: <input type='password' name='password'><br>\n"
           "<input type='submit' value='Login'>\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login() {
    char username[50];
    char password[50];

    printf("Content-Type: text/html\n\n");

    // Simulate reading POST data
    sscanf("username=admin&password=1234", "username=%49[^&]&password=%49s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("<html>\n"
               "<head><title>Admin Page</title></head>\n"
               "<body>\n"
               "<h1>Welcome to the Admin Page!</h1>\n"
               "</body>\n"
               "</html>\n");
    } else {
        printf("<html>\n"
               "<head><title>Login Failed</title></head>\n"
               "<body>\n"
               "<h1>Invalid username or password.</h1>\n"
               "<a href='/login'>Try again</a>\n"
               "</body>\n"
               "</html>\n");
    }
}

int main() {
    // Simulating a request environment
    char method[10];
    sscanf("GET", "%9s", method);

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }

    return 0;
}