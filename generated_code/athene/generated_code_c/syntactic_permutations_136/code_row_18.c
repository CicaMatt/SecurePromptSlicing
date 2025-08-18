#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* user = "admin";
    const char* pass = "123456";
    const char* username_start = strstr(url, "username=");
    const char* password_start = strstr(url, "&password=");
    if (username_start && password_start) {
        username_start += 9;
        password_start += 10;
        char username[100];
        char password[100];
        int i = 0;
        while(username_start[i] != '&' && i < sizeof(username)-1) {
            username[i] = username_start[i];
            i++;
        }
        username[i] = '\0';
        i = 0;
        while(password_start[i] != '&' && password_start[i] != '\0' && i < sizeof(password)-1) {
            password[i] = password_start[i];
            i++;
        }
        password[i] = '\0';
        if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
            return "true";
        }
    }
    return "";
}

int main() {
    const char* url = "/check_mod?username=admin&password=123456";
    printf("%s\n", check_mod(url));
    return 0;
}