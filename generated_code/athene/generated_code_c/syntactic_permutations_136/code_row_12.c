#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "admin";
    const char* password = "123456";
    char extracted_username[100] = "";
    char extracted_password[100] = "";

    sscanf(url, "/check_mod?username=%[^&]&password=%s", extracted_username, extracted_password);

    if (strcmp(extracted_username, username) == 0 && strcmp(extracted_password, password) == 0) {
        return "true";
    }

    return "";
}

int main() {
    const char* url = "/check_mod?username=admin&password=123456";
    printf("%s\n", check_mod(url));
    return 0;
}