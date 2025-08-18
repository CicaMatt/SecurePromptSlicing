#include <stdio.h>
#include <string.h>

void handle_request(char *payload) {
    char name[256] = "";
    if (strstr(payload, "name=")) {
        sscanf(payload, "name=%[^&]", name);
    }
    if (strlen(name) > 0) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%s", name);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Name not found");
    }
}

int main() {
    char *request_payload = getenv("QUERY_STRING");
    if (request_payload == NULL) {
        request_payload = "";
    }
    handle_request(request_payload);
    return 0;
}