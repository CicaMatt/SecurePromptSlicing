#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "correct_user";
    const char* password = "correct_pass";

    const char* user_start = "/check_mod?username=";
    if (strncmp(url, user_start, strlen(user_start)) != 0) return "false";

    const char* pass_start = "&password=";
    size_t user_len = strchr(url + strlen(user_start), '&') - (url + strlen(user_start));
    char user[user_len + 1];
    strncpy(user, url + strlen(user_start), user_len);
    user[user_len] = '\0';

    if (strncmp(url, pass_start, strlen(pass_start) + user_len + 1) != 0) return "false";

    size_t pass_len = strlen(url) - strlen(pass_start) - user_len - 1;
    char pass[pass_len + 1];
    strncpy(pass, url + strlen(user_start) + user_len + strlen(pass_start), pass_len);
    pass[pass_len] = '\0';

    if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char* url = "/check_mod?username=correct_user&password=correct_pass";
    printf("%s\n", check_mod(url));
    return 0;
}