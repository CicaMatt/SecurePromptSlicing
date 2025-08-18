#include <stdio.h>
#include <string.h>

char* check_credentials(const char* username, const char* password) {
    static const char* valid_username = "user";
    static const char* valid_password = "pass";
    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return "true";
    }
    return "";
}

char* handle_request(const char* url) {
    char username[100] = "", password[100] = "";
    sscanf(url, "/?username=%[^&]&password=%s", username, password);
    return check_credentials(username, password);
}