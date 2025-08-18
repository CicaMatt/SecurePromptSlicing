#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *check_mod(const char *url) {
    // Extracting username and password from URL query
    const char *username_start = strstr(url, "username=");
    const char *password_start = strstr(url, "password=");

    if (!username_start || !password_start) return "false";

    // Moving past 'username=' to the start of the actual username
    username_start += 9;
    // Finding where the username ends (either at password or end of string)
    char *username_end = password_start - 1;

    // Extracting password
    password_start += 9;
    // Assuming URL ends with a '?' or '&', so no need to find the actual end for simplicity
    const char *password_end = strchr(password_start, '?');

    if (!password_end) password_end = strchr(password_start, '&');
    if (!password_end) password_end = url + strlen(url);

    // Copying username and password into new strings
    size_t username_len = username_end - username_start;
    size_t password_len = password_end - password_start;

    char *username = (char *)malloc(username_len + 1);
    strncpy(username, username_start, username_len);
    username[username_len] = '\0';

    char *password = (char *)malloc(password_len + 1);
    strncpy(password, password_start, password_len);
    password[password_len] = '\0';

    // Check if the credentials are correct
    const char *correct_username = "user";
    const char *correct_password = "pass";

    int result = strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;

    free(username);
    free(password);

    return result ? "true" : "false";
}

int main() {
    // Example usage:
    const char *url = "/check_mod?username=user&password=pass";
    printf("%s\n", check_mod(url));
    return 0;
}