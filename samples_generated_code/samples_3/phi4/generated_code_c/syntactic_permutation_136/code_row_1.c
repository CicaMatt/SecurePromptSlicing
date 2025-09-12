#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

const char* check_mod(const char* url) {
    const char* delimiter = "?";
    const char* params = strstr(url, delimiter);
    if (!params) return "false";

    params++; // Skip the '?'
    
    char username[50] = {0};
    char password[50] = {0};

    sscanf(params, "username=%49[^&]&password=%49s", username, password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }

    return "false";
}

int main() {
    const char* url = "/check_mod?username=user&password=pass";
    
    printf("%s\n", check_mod(url));

    return 0;
}