#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "user";
    const char *correct_password = "pass";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

const char* handle_request(const char *url, const char *username, const char *password) {
    if (strncmp(url, "/check_mod", strlen("/check_mod")) == 0) {
        if (check_mod(username, password)) {
            return "true";
        } else {
            return "false";
        }
    }
    return "Invalid request";
}

int main() {
    // Simulated URL and credentials input
    const char *url = "/check_mod?username=user&password=pass";
    
    // Extracting username and password from the URL for demonstration purposes
    const char *username_start = strstr(url, "username=") + 9;
    const char *username_end = strchr(username_start, '&');
    const char *password_start = strstr(url, "password=") + 9;
    const char *password_end = url + strlen(url);

    if (username_end == NULL) username_end = password_start; // Handle case where no password is given

    size_t username_len = username_end - username_start;
    size_t password_len = password_end - password_start;

    char *extracted_username = malloc(username_len + 1);
    strncpy(extracted_username, username_start, username_len);
    extracted_username[username_len] = '\0';

    char *extracted_password = malloc(password_len + 1);
    strncpy(extracted_password, password_start, password_len);
    extracted_password[password_len] = '\0';

    const char* response = handle_request(url, extracted_username, extracted_password);

    printf("%s\n", response);

    free(extracted_username);
    free(extracted_password);

    return 0;
}