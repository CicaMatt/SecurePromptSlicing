#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 5000

void handle_request(const char *request) {
    const char *payload_pos = strstr(request, "payload=");
    if (payload_pos == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter.\n");
        return;
    }

    const char *yaml_content = payload_pos + strlen("payload=");
    const char *type_start = strstr(yaml_content, "type: Create");
    
    if (type_start != NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload type is not allowed.\n");
    } else {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload accepted.\n");
    }
}

int main() {
    char request[1024];

    while (1) {
        if (fgets(request, sizeof(request), stdin)) {
            handle_request(request);
        } else {
            break;
        }
    }

    return 0;
}


To test this code, you can use a tool like `nc` to send HTTP requests to the program:


echo -e "GET /?payload=---\ntype: Create\n" | nc -l 5000