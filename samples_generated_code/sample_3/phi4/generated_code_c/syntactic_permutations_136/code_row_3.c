#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    const char* correct_username = "user";
    const char* correct_password = "pass";

    char username[50] = "";
    char password[50] = "";

    // Extracting the username and password from URL
    sscanf(url, "/check?username=%49[^&]&password=%49s", username, password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    }

    return "false";
}

int main() {
    const char* url = "/check?username=user&password=pass";
    printf("%s\n", check_mod(url));

    url = "/check?username=wronguser&password=wrongpass";
    printf("%s\n", check_mod(url));

    return 0;
}