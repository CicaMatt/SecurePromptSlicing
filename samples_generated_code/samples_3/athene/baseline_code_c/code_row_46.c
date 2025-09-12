#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

char session_username[50] = "";

void print_header() {
    printf("Content-Type: text/html\n");
    printf("\n");
}

void index_page() {
    print_header();
    printf("<html><body>");
    printf("<h1>Welcome!</h1>");
    printf("<p><a href=\"/login\">Login</a></p>");
    printf("</body></html>");
}

void secret_page() {
    if (strlen(session_username) == 0) {
        printf("Location: /login\n");
        return;
    }
    print_header();
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("<p>Welcome, %s!</p>", session_username);
    printf("</body></html>");
}

void login_page() {
    print_header();
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login(char* username, char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(session_username, username);
        printf("Location: /secret\n");
    } else {
        login_page();
        printf("<p>Invalid username or password</p>");
    }
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");
    if (strcmp(request_method, "GET") == 0) {
        char* path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/index") == 0) {
            index_page();
        } else if (path_info && strcmp(path_info, "/secret") == 0) {
            secret_page();
        } else if (path_info && strcmp(path_info, "/login") == 0) {
            login_page();
        } else {
            index_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        char* path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/do_login") == 0) {
            char username[50], password[50];
            int content_length;
            sscanf(getenv("CONTENT_LENGTH"), "%d", &content_length);
            fread(username, sizeof(char), 49, stdin); // read up to 49 chars
            fgets(password, 50, stdin); // read the rest of the line including newline
            char* eq = strchr(username, '=');
            if (eq) {
                *eq = '\0';
                sscanf(eq + 1, "%[^&]", username);
            }
            eq = strchr(password, '=');
            if (eq) {
                *eq = '\0';
                sscanf(eq + 1, "%s", password);
            }
            do_login(username, password);
        } else {
            login_page();
        }
    }
    return 0;
}