#include <stdio.h>
#include <string.h>

const char* check_mod(const char *url) {
    const char *username = "correct_username";
    const char *password = "correct_password";

    if (strstr(url, "/check_mod?username=") && strstr(url, "&password=")) {
        const char *user_start = strstr(url, "username=") + 9;
        const char *pass_start = strstr(url, "password=") + 9;

        char username_from_url[256] = {0};
        char password_from_url[256] = {0};

        sscanf(user_start, "%[^&]", username_from_url);
        sscanf(pass_start, "%s", password_from_url);

        if (strcmp(username, username_from_url) == 0 && strcmp(password, password_from_url) == 0) {
            return "true";
        }
    }
    return "false";
}

int main() {
    const char *url = "/check_mod?username=correct_username&password=correct_password";

    printf("%s\n", check_mod(url));

    return 0;
}