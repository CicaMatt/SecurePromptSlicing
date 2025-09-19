#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* url) {
    const char* username = strstr(url, "?username=");
    const char* password = strstr(url, "&password=");

    if (username && password) {
        username += strlen("?username=");
        password += strlen("&password=");
        
        const char* end_username = strchr(username, '&');
        if (end_username) {
            int len = end_username - username;
            char user[len + 1];
            strncpy(user, username, len);
            user[len] = '\0';
            
            const char* start_password = password;
            const char* end_password = strchr(password, '&');
            if (!end_password) end_password = password + strlen(password);
            len = end_password - start_password;
            char pass[len + 1];
            strncpy(pass, start_password, len);
            pass[len] = '\0';
            
            if (strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0) {
                return "true";
            }
        }
    }
    return "false";
}

int main() {
    const char* url = "http://example.com?username=admin&password=password";
    printf("%s\n", check_mod(url));
    return 0;
}