#include <stdio.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 1024

void process_payload(const char *payload, char *output) {
    int i, j;
    size_t payload_len = strlen(payload);
    const char *field_name = "name=\"";
    size_t field_name_len = strlen(field_name);

    for (i = 0; i < payload_len - field_name_len + 1; ++i) {
        if (strncmp(&payload[i], field_name, field_name_len) == 0) {
            j = i + field_name_len;
            while (j < payload_len && payload[j] != '\"') {
                *output++ = payload[j++];
            }
            *output = '\0';
            return;
        }
    }

    // If 'name' field is not found, output an empty string
    *output = '\0';
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];
    char name[256];

    // Simulate receiving a payload from user request
    printf("Enter the payload: ");
    fgets(payload, MAX_PAYLOAD_SIZE, stdin);

    process_payload(payload, name);

    if (strlen(name) > 0) {
        printf("Name: %s\n", name);
    } else {
        printf("Field 'name' not found.\n");
    }

    return 0;
}