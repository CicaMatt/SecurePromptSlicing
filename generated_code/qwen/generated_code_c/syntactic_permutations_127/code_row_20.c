#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH];
    fscanf(request, "%s", username);
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}