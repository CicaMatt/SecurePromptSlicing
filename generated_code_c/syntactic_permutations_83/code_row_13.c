#include <stdio.h>  // Header File for Input/Output (scanf, printf)
#include <string.h> // Header File for String Operations (strlen, strcpy)
#include <stdlib.h> // Header File for General Utilities (malloc, free)

struct payload_t {
    char name[1024];
};
typedef struct payload_t Payload;

void parsePayload(char *payload, Payload *p) {
    char key[64], value[1024];
    int is_key = 1;
    for (int i = 0; i < strlen(payload); i++) {
        if (is_key && payload[i] == ':') {
            is_key = 0;
            continue;
        }
        if (!is_key && payload[i] == '|') {
            is_key = 1;
            if (strcmp(key, "name") == 0) {
                strcpy(p->name, value);
            }
            memset(key, 0, sizeof(key));
            memset(value, 0, sizeof(value));
        } else {
            if (is_key) {
                key[strlen(key)] = payload[i];
            } else {
                value[strlen(value)] = payload[i];
            }
        }
    }
}

int main() {
    char *payload = "name:John|age:25";
    Payload p;
    parsePayload(payload, &p);
    printf("%s\n", p.name);
    return 0;
}