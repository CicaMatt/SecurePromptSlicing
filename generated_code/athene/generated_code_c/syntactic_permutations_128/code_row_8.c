#include <stdio.h>
#include <string.h>

void handle_request(FILE *request, FILE *response) {
    char username[100];
    fscanf(request, "%s", username);
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        return 1;
    }

    handle_request(request, response);

    fclose(request);
    fclose(response);

    return 0;
}