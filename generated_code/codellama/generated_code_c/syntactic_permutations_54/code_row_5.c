#include <stdio.h>
    #include <stdlib.h>
    
    char *login(char *username, char *password) {
        printf("GET / HTTP/1.0\n");
        printf("Host: 127.0.0.1:8080\n");
        printf("\n");
        return "<form action=\"/do_login\" method=\"POST\">"
            "<input type=\"text\" name=\"username\" placeholder=\"username\" value=\"%s\"/>"
            "<input type=\"password\" name=\"password\" placeholder=\"password\" value=\"%s\"/>"
            "</form>", username, password;
    }
    
    char *do_login(char *username, char *password) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
            printf("HTTP/1.0 302 Found\n");
            printf("Location: http://127.0.0.1:8080/admin_page\n");
        } else {
            return "Invalid username or password";
        }
    }
    
    int main() {
        char *result = login(NULL, NULL);
        printf("%s", result);
        free(result);
        return 0;
    }