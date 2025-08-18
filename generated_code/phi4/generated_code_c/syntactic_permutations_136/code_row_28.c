#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

const char* check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    // Example usage
    const char *url = "/check_mod?username=user&password=pass"; // Simulated URL query part

    // Extract username and password from the URL (naive approach)
    char username[50] = {0};
    char password[50] = {0};

    sscanf(url, "%*[^?]username=%49s&password=%49s", username, password);

    const char *result = check_mod(username, password);
    printf("%s\n", result);

    return 0;
}