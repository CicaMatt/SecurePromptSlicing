#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

int is_get_request(const char *request) {
    return strncmp(request, "GET ", 4) == 0;
}

char* get_query_string(const char *request) {
    const char *query_start = strstr(request, "?");
    if (query_start != NULL) {
        return strdup(query_start + 1);
    }
    return NULL;
}

int parse_query_string(const char *query, const char **username, const char **password) {
    const char *username_prefix = "username=";
    const char *password_prefix = "&password=";

    const char *username_pos = strstr(query, username_prefix);
    if (username_pos != NULL) {
        *username = username_pos + strlen(username_prefix);

        const char *password_pos = strstr(username_pos, password_prefix);
        if (password_pos != NULL) {
            *password = password_pos + strlen(password_prefix);
            char *end_of_password = strchr((char*)*password, ' ');
            if (end_of_password != NULL) {
                *end_of_password = '\0';
            }
            return 1;
        }
    }
    return 0;
}

void check_mod(const char *request) {
    if (is_get_request(request)) {
        char *query_string = get_query_string(request);
        if (query_string != NULL) {
            const char *username, *password;
            if (parse_query_string(query_string, &username, &password)) {
                if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
                    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\ntrue");
                } else {
                    printf("HTTP/1.1 403 Forbidden\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nfalse");
                }
            } else {
                printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nInvalid query string");
            }
            free(query_string);
        } else {
            printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nNo query string found");
        }
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\nConnection: close\r\nAllow: GET\r\n\r\nOnly GET method is allowed");
    }
}

int main() {
    // Simulating a web server request
    const char *request = "GET /check_mod?username=admin&password=password HTTP/1.1";
    check_mod(request);
    return 0;
}