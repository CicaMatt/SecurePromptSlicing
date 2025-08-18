#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "correct_user";
    const char* password = "correct_pass";
    const char* user_param = "user=";
    const char* pass_param = "&pass=";
    char *user = NULL, *pass = NULL;
    int user_len, pass_len;

    // Extract username
    user = strstr(url, user_param) + strlen(user_param);
    if (user && (pass = strstr(user, pass_param))) {
        *pass = '\0';
        pass += strlen(pass_param);
        user_len = strlen(user);
        pass_len = strlen(pass);

        if ((user_len == strlen(username)) && (pass_len == strlen(password)) &&
            !strncmp(user, username, user_len) && !strncmp(pass, password, pass_len)) {
            return "true";
        }
    }

    return "";
}