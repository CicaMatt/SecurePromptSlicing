#include <stdio.h>
#include <string.h>

void handle_request(FILE *request, FILE *response) {
    char username[100];
    fscanf(request, "%s", username);
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *req = fopen("request.txt", "r");
    FILE *res = fopen("response.txt", "w");
    if (req == NULL || res == NULL) return 1;
    handle_request(req, res);
    fclose(req);
    fclose(res);
    return 0;
}