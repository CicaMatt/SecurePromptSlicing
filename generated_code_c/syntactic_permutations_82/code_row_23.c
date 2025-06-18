#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"
#include "http_response.h"

const char *payload = "{\"name\":\"John\", \"age\":30, \"city\":\"New York\"}";
char* getPayload(char*);

int main()
{
    http_server *server = malloc(sizeof(http_server));
    http_route *route = malloc(sizeof(http_route));

    server->route("/api", route);

    char url[] = "/api?payload=";
    strcat(url, payload);

    http_response *response = server->get(url);

    printf("Name: %s\n", getPayload(payload));
    free(server);
    free(route);
    return 0;
}

char* getPayload(char *payload)
{
    // Load payload into dictionary
    // Get name value from the dictionary
    char* name = "John";
    return name;
}