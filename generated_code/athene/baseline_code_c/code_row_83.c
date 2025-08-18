#include <stdio.h>
#include <string.h>

void handle_request(char *payload) {
    char name[100] = "";
    if (strstr(payload, "name=")) {
        sscanf(payload, "name=%[^&]", name);
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%s", name);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("No 'name' field found.");
    }
}

int main() {
    char request[] = "name=John Doe&age=30"; // Example payload
    handle_request(request);
    return 0;
}