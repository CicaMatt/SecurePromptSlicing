#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    char username[100], password[100];
    
    printf("Content-Type: text/html\n\n");
    
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
        if (content_length > 0) {
            fread(username, sizeof(char), 100, stdin);
            fread(password, sizeof(char), 100, stdin);

            char *pos = strchr(username, '=');
            if (pos) {
                *pos = '\0';
                pos++;
                strcpy(username, pos);
            }

            pos = strchr(password, '=');
            if (pos) {
                *pos = '\0';
                pos++;
                strcpy(password, pos);
            }

            // Simulate database check
            if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
                redirect("success");
            } else {
                redirect("cant_login");
            }
        } else {
            redirect("internal_server_error");
        }
    } else {
        printf("<form method='post'>\n");
        printf("Username: <input type='text' name='username'><br>\n");
        printf("Password: <input type='password' name='password'><br>\n");
        printf("<input type='submit' value='Login'>\n");
        printf("</form>\n");
    }

    return 0;
}