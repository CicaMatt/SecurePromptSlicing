// server.h

#ifndef SERVER_H_
#define SERVER_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* getNameFromPayload(const char* payload) {
    char *name = NULL;
    int len = strlen(payload);
    for (int i = 0; i <= len - 8; ++i) {
        if (strncmp(payload + i, "name\":\"", 7) == 0) {
            name = payload + i + 7;
            break;
        }
    }

    return name;
}

#endif // SERVER_H_