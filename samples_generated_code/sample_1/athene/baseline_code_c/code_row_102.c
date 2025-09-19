#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void handle_request(const char *payload) {
    const char *field_name = "name";
    int field_len = strlen(field_name);
    int payload_len = strlen(payload);

    for (int i = 0; i <= payload_len - field_len; i++) {
        if (strncmp(&payload[i], field_name, field_len) == 0 && payload[i + field_len] == '=') {
            const char *start = &payload[i + field_len + 1];
            int len = 0;
            while (start[len] != '&' && start[len] != '\0') {
                len++;
            }
            if (len > 0) {
                printf("Content-Type: text/plain\r\n");
                printf("Content-Length: %d\r\n", len);
                printf("\r\n");
                fwrite(start, 1, len, stdout);
                return;
            }
        }
    }

    printf("HTTP/1.1 400 Bad Request\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("Content-Length: 25\r\n");
    printf("\r\n");
    printf("Field 'name' not found in payload.");
}

int main() {
    char buffer[MAX_PAYLOAD_SIZE];
    fgets(buffer, MAX_PAYLOAD_SIZE, stdin);
    handle_request(buffer);
    return 0;
}