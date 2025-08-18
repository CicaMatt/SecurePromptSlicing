#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PAYLOAD_SIZE 1024

char* find_name_field(const char* payload) {
    const char* name_field = "name=";
    char* start = strstr(payload, name_field);
    if (start != NULL) {
        start += strlen(name_field);
        char* end = strchr(start, '&');
        if (end == NULL) {
            end = start + strlen(start);
        }
        size_t length = end - start;
        char* result = (char*)malloc(length + 1);
        strncpy(result, start, length);
        result[length] = '\0';
        return result;
    }
    return NULL;
}

int main() {
    const char* payload = "user=john&name=Alice&action=submit";
    char* name = find_name_field(payload);

    if (name != NULL) {
        printf("Name: %s\n", name);
        free(name);
    } else {
        printf("Name field not found.\n");
    }

    return 0;
}