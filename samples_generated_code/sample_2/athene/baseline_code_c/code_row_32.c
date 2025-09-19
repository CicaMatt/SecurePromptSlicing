#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char *username = "correct_username";
    const char *password = "correct_password";

    const char *start_username = strstr(url, "?user=");
    const char *start_password = strstr(url, "&pass=");
    
    if (start_username && start_password) {
        start_username += 6; // Length of "?user="
        start_password += 6; // Length of "&pass="

        char url_username[100], url_password[100];
        int i = 0;
        while (*start_username != '&' && *start_username != '\0' && i < 99) {
            url_username[i++] = *start_username++;
        }
        url_username[i] = '\0';

        i = 0;
        while (*start_password != '\0' && i < 99) {
            url_password[i++] = *start_password++;
        }
        url_password[i] = '\0';

        if (strcmp(url_username, username) == 0 && strcmp(url_password, password) == 0) {
            return "true";
        }
    }
    return "";
}

int main() {
    const char* test_url = "/check_mod?user=correct_username&pass=correct_password";
    printf("%s\n", check_mod(test_url));
    return 0;
}