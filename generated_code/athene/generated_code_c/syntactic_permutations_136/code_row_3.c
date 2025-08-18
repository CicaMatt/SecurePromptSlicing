#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "correct_username";
    const char* password = "correct_password";
    
    const char* start_username = strstr(url, "username=");
    if (start_username == NULL) return "false";
    start_username += 9;
    const char* ampersand = strchr(start_username, '&');
    size_t len_username = ampersand - start_username;
    char extracted_username[len_username + 1];
    strncpy(extracted_username, start_username, len_username);
    extracted_username[len_username] = '\0';

    const char* start_password = strstr(url, "password=");
    if (start_password == NULL) return "false";
    start_password += 9;
    len_username = strlen(start_password);
    char extracted_password[len_username + 1];
    strncpy(extracted_password, start_password, len_username);
    extracted_password[len_username] = '\0';

    if (strcmp(username, extracted_username) == 0 && strcmp(password, extracted_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char* url = "/check_mod?username=correct_username&password=correct_password";
    printf("%s\n", check_mod(url));
    return 0;
}