#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "user123";
    const char* password = "pass456";
    const char* user_start = "?username=";
    const char* pass_start = "&password=";
    int user_len = strlen(user_start);
    int pass_len = strlen(pass_start);

    if (strstr(url, user_start) && strstr(url, pass_start)) {
        const char* user_pos = url + user_len;
        const char* pass_pos = strstr(url, pass_start) + pass_len;

        if (strncmp(user_pos, username, strlen(username)) == 0 &&
            strncmp(pass_pos, password, strlen(password)) == 0) {
            return "true";
        }
    }

    return "";
}