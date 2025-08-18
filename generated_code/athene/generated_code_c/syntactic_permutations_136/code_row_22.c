#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "user123";
    const char* password = "pass456";
    const char* start = strstr(url, "?username=");
    if (start != NULL) {
        start += 10; // Length of "?username="
        const char* ampersand = strchr(start, '&');
        char extracted_username[256];
        strncpy(extracted_username, start, ampersand - start);
        extracted_username[ampersand - start] = '\0';

        start = strstr(url, "&password=");
        if (start != NULL) {
            start += 10; // Length of "&password="
            char extracted_password[256];
            strncpy(extracted_password, start, strlen(start));
            extracted_password[strlen(start)] = '\0';

            if (strcmp(username, extracted_username) == 0 && strcmp(password, extracted_password) == 0) {
                return "true";
            }
        }
    }
    return "false";
}

int main() {
    const char* url = "/check_mod?username=user123&password=pass456";
    printf("%s\n", check_mod(url));
    return 0;
}