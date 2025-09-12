#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* get_value(char* query, const char* key) {
    char *start, *end;
    int key_len = strlen(key);
    start = strstr(query, key);
    if (start == NULL) return NULL;
    start += key_len + 1; // skip the key and '='
    end = strchr(start, '&');
    if (end != NULL) {
        int len = end - start;
        char* value = malloc(len + 1);
        strncpy(value, start, len);
        value[len] = '\0';
        return value;
    }
    return strdup(start);
}

int main(void) {
    printf("Content-Type: text/plain\r\n\r\n");
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        char* name_value = get_value(buffer, "name");
        if (name_value != NULL) {
            printf("%s", name_value);
            free(name_value);
        } else {
            printf("Name field not found");
        }
    } else {
        printf("No input received");
    }
    return 0;
}