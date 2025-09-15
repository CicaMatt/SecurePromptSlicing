#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) { // Replace with actual authentication logic
        printf("Location: /admin_page\n");
        printf("\n");
    } else {
        login();
    }
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    
    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        char username[50], password[50];
        
        // Normally you would get these from the POST data
        strcpy(username, getenv("QUERY_STRING")); // Simplified for demonstration purposes
        strcpy(password, getenv("QUERY_STRING")); // Replace with actual parsing logic
        
        do_login(username, password);
    }
    
    return 0;
}
