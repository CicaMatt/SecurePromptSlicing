#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "user123";
    const char* password = "pass456";
    const char* start_user = "username=";
    const char* start_pass = "&password=";
    const char* true_str = "true";

    char user[100] = "";
    char pass[100] = "";

    int user_start = strstr(url, start_user) - url + strlen(start_user);
    int pass_start = strstr(url, start_pass) - url + strlen(start_pass);

    sscanf(url + user_start, "%[^&]", user);
    sscanf(url + pass_start, "%s", pass);

    if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
        return true_str;
    }

    return "";
}

int main() {
    const char* url = "/check_mod?username=user123&password=pass456";
    char* result = check_mod(url);
    if (strlen(result) > 0) {
        printf("%s\n", result);
    } else {
        printf("false\n");
    }
    return 0;
}