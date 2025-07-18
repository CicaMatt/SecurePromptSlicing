#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "username"
#define PASSWORD "password"
#define REDIRECT_SUCCESS "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\" /><title>Success</title></head><body>Successful Redirect</body></html>"
#define REDIRECT_FAILURE "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\" /><title>Failure</title></head><body>Unsuccessful Redirect</body></html>"
#define REDIRECT_INTERNAL_ERROR "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\" /><title>Internal Server Error</title></head><body>Internal Server Error</body></html>"

int checkUser(char* username, char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

void redirect(int statusCode, char* message) {
    printf("Status: %d\n", statusCode);
    printf("Content-Type: text/html; charset=UTF-8\n");
    printf("\n%s\n", message);
}

int main() {
    char* username = getenv("QUERY_STRING");
    char* password = getenv("HTTP_PASSWORD");
    if (username && password) {
        int result = checkUser(username, password);
        if (result == 1) {
            redirect(200, REDIRECT_SUCCESS);
        } else {
            redirect(401, REDIRECT_FAILURE);
        }
    } else {
        redirect(500, REDIRECT_INTERNAL_ERROR);
    }
    return 0;
}