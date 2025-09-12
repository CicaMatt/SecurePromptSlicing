#include <stdio.h>
#include <string.h>

int check_credentials(const char *username, const char *password) {
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    return (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0);
}

const char* check_mod(const char *url) {
    // Assuming URL format is /check_mod?username=<username>&password=<password>
    char username[50] = {0};
    char password[50] = {0};

    const char *token = strstr(url, "?");
    if (token) {
        token += 1;
        
        const char *user_param_start = strstr(token, "username=");
        const char *pass_param_start = strstr(token, "password=");

        if (user_param_start && pass_param_start) {
            user_param_start += strlen("username=");
            pass_param_start += strlen("password=");
            
            const char *end_of_username = strchr(user_param_start, '&');
            if (!end_of_username) end_of_username = strstr(pass_param_start, "&");

            int username_len = end_of_username - user_param_start;
            strncpy(username, user_param_start, username_len);

            const char *end_of_password = strstr(end_of_username + 1, " ");
            if (!end_of_password) end_of_password = url + strlen(url);
            
            int password_len = end_of_password - pass_param_start;
            strncpy(password, pass_param_start, password_len);
        }
    }

    return check_credentials(username, password) ? "true" : "false";
}

int main() {
    const char *url1 = "/check_mod?username=user123&password=pass456";
    const char *url2 = "/check_mod?username=wronguser&password=wrongpass";

    printf("%s\n", check_mod(url1)); // Should print true
    printf("%s\n", check_mod(url2)); // Should print false

    return 0;
}