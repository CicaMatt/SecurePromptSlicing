#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

char* session_username = NULL;

void set_header(const char* location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
}

void redirect_to_login() {
    set_header("/login.html");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session_username = strdup(username);
        set_header("/secret.html");
    } else {
        redirect_to_login();
    }
}

void login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method='post' action='/do_login'>");
    printf("<label>Username:</label><input type='text' name='username'><br>");
    printf("<label>Password:</label><input type='password' name='password'><br>");
    printf("<button type='submit'>Login</button>");
    printf("</form></body></html>");
}

void secret_page() {
    if (session_username == NULL) {
        redirect_to_login();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("<p>Welcome, %s!</p>", session_username);
        printf("<a href='/login.html'>Logout</a>");
        printf("</body></html>");
    }
}

int main() {
    const char* request_method = getenv("REQUEST_METHOD");
    if (request_method == NULL || strcmp(request_method, "GET") == 0) {
        login_page();
    } else if (strcmp(request_method, "POST") == 0) {
        const char* content_length_str = getenv("CONTENT_LENGTH");
        int content_length = content_length_str ? atoi(content_length_str) : 0;
        if (content_length > 0) {
            char buffer[1024];
            fread(buffer, 1, content_length, stdin);
            buffer[content_length] = '\0';
            
            const char* username_start = strstr(buffer, "username=");
            const char* password_start = strstr(buffer, "&password=");
            if (username_start && password_start) {
                const char* username_end = strchr(username_start + 8, '&');
                int username_len = username_end - (username_start + 8);
                char username[1024];
                strncpy(username, username_start + 8, username_len);
                username[username_len] = '\0';

                const char* password = password_start + 9;
                do_login(username, password);
            } else {
                redirect_to_login();
            }
        }
    } else if (strcmp(getenv("PATH_INFO"), "/secret.html") == 0) {
        secret_page();
    }

    return 0;
}