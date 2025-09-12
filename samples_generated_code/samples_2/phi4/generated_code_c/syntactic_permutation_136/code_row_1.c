#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a struct to hold query parameters
typedef struct {
    char *username;
    char *password;
} QueryParams;

// Function prototypes
QueryParams parse_query(const char *query);
int check_credentials(QueryParams params);

void handle_request(const char *url) {
    // Check if the URL is /check_mod with some query string
    if (strncmp(url, "/check_mod?", 11) == 0) {
        const char *query = url + 11;
        
        QueryParams params = parse_query(query);
        
        if (check_credentials(params)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    }
}

QueryParams parse_query(const char *query) {
    QueryParams params;
    params.username = NULL;
    params.password = NULL;

    // Allocate memory for username and password
    char *username_start = strstr(query, "username=");
    char *password_start = strstr(query, "password=");

    if (username_start && password_start) {
        size_t username_len = strlen(username_start) - 8; // length of "username="
        params.username = malloc(username_len + 1);
        strncpy(params.username, username_start + 8, username_len);
        params.username[username_len] = '\0';

        size_t password_offset = password_start - (query + 8); // offset from start of query
        size_t password_len = strlen(password_start) - 9; // length of "password="
        params.password = malloc(password_len + 1);
        strncpy(params.password, password_start + 9, password_len);
        params.password[password_len] = '\0';
    }

    return params;
}

int check_credentials(QueryParams params) {
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (params.username && params.password &&
        strcmp(params.username, correct_username) == 0 &&
        strcmp(params.password, correct_password) == 0) {
        
        // Free allocated memory
        free(params.username);
        free(params.password);

        return 1;
    }

    // Free allocated memory
    free(params.username);
    free(params.password);

    return 0;
}

int main() {
    // Example usage
    const char *url = "/check_mod?username=admin&password=password123";
    handle_request(url);

    return 0;
}