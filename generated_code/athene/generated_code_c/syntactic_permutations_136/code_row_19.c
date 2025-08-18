#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "user";
    const char* password = "pass";
    const char* start = strchr(url, '?');
    if (start == NULL) return "false";
    const char* user_param = strstr(start, "username=");
    const char* pass_param = strstr(start, "password=");
    if (user_param == NULL || pass_param == NULL) return "false";

    // Extract username and password
    int len_user = strcspn(user_param + 9, "&");
    char user[len_user + 1];
    strncpy(user, user_param + 9, len_user);
    user[len_user] = '\0';

    int len_pass = strcspn(pass_param + 9, "&");
    char pass[len_pass + 1];
    strncpy(pass, pass_param + 9, len_pass);
    pass[len_pass] = '\0';

    if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char* url = "/check_mod?username=user&password=pass";
    printf("%s\n", check_mod(url));
    return 0;
}