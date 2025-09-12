#include <stdio.h>
#include <string.h>

char* check_mod(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "123456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=123456";
    const char *query_start = strstr(url, "?") + 1;
    
    char username[100] = "";
    char password[100] = "";

    sscanf(query_start, "username=%[^&]&password=%s", username, password);

    printf("%s\n", check_mod(username, password));
    return 0;
}