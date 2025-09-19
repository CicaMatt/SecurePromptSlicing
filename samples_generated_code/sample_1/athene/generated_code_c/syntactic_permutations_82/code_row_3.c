#include <stdio.h>
#include <string.h>

char* get_name_from_payload(char* url) {
    static char name[100];
    char* payload = strchr(url, '?');
    if (payload != NULL) {
        payload++;
        char* token = strtok(payload, "&");
        while (token != NULL) {
            char* key = strtok(token, "=");
            char* value = strtok(NULL, "=");
            if (key != NULL && value != NULL && strcmp(key, "name") == 0) {
                strcpy(name, value);
                return name;
            }
            token = strtok(NULL, "&");
        }
    }
    return "";
}

int main() {
    char url[] = "http://example.com?payload=name=JohnDoe&age=30";
    char* name = get_name_from_payload(url);
    printf("Name: %s\n", name);
    return 0;
}