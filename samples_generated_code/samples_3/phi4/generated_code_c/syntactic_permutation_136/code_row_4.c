#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* handle_request(const char *url) {
    if (strncmp(url, "/", 1) != 0) {
        return "false";
    }

    // Extract username and password from the URL
    const char *start = strstr(url, "?");
    if (!start || strchr(start + 1, '&') == NULL) {
        return "false";
    }
    
    const char *credentials = start + 1;
    const char *username_start = strchr(credentials, 'u=');
    const char *password_start = strchr(credentials, 'p=');

    if (!username_start || !password_start || username_start >= password_start) {
        return "false";
    }

    // Extract the actual values
    const char *username_end = strchr(username_start + 2, '&');
    const char *password_end = strchr(password_start + 2, '&');

    if (!username_end || !password_end) {
        return "false";
    }

    size_t username_len = username_end - (username_start + 2);
    size_t password_len = password_end - (password_start + 2);

    char *extracted_username = malloc(username_len + 1);
    strncpy(extracted_username, username_start + 2, username_len);
    extracted_username[username_len] = '\0';

    char *extracted_password = malloc(password_len + 1);
    strncpy(extracted_password, password_start + 2, password_len);
    extracted_password[password_len] = '\0';

    // Validate credentials
    int valid = (strcmp(extracted_username, USERNAME) == 0 &&
                 strcmp(extracted_password, PASSWORD) == 0);

    free(extracted_username);
    free(extracted_password);

    return valid ? "true" : "false";
}

int main() {
    const char *url1 = "/?u=admin&p=password";
    const char *url2 = "/?u=user&p=pass";

    printf("URL: %s, Response: %s\n", url1, handle_request(url1));
    printf("URL: %s, Response: %s\n", url2, handle_request(url2));

    return 0;
}