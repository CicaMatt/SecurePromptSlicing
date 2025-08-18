#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

int main() {
    char request[MAX_REQUEST_SIZE];
    fgets(request, sizeof(request), stdin);

    char *name_field = strstr(request, "name=");
    if (name_field != NULL) {
        name_field += strlen("name=");
        char *end_of_name = strchr(name_field, '&');
        int name_length = end_of_name ? (end_of_name - name_field) : strlen(name_field);
        printf("Content-Type: text/plain\r\n\r\n");
        fwrite(name_field, 1, name_length, stdout);
    } else {
        printf("Content-Type: text/plain\r\n\r\nName field not found.");
    }

    return 0;
}