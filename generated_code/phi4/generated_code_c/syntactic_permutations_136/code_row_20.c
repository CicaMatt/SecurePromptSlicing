#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int authenticate(const char *username, const char *password) {
    // Example credentials for demonstration purposes
    return strcmp(username, "user") == 0 && strcmp(password, "pass") == 0;
}

void check_mod(const char *url) {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    // Extracting username and password from URL assuming format /check_mod?username=user&password=pass
    sscanf(url, "/check_mod?username=%255[^&]&password=%255s", username, password);

    if (authenticate(username, password)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    const char *url = "/check_mod?username=user&password=pass";
    check_mod(url);
    return 0;
}