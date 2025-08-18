#include <stdio.h>
#include <string.h>

void send_response(FILE *response, const char *username) {
    char greeting[256];
    snprintf(greeting, sizeof(greeting), "hello %s", username);
    fprintf(response, "%s\n", greeting);
}

int main() {
    FILE *response = fopen("response.txt", "w");
    if (response == NULL) return 1;
    
    const char *username = "client_username";
    send_response(response, username);
    
    fclose(response);
    return 0;
}