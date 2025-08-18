#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mongoose.h"

#define PORT 5000

typedef struct {
    char *type;
} payload_t;

int parse_yaml(const char *yaml, size_t yaml_len, payload_t *payload) {
    const char *start = strstr(yaml, "type:");
    if (start == NULL) return -1;

    start += 5; // Move past 'type:'
    while (*start && isspace((unsigned char)*start)) start++; // Skip whitespace

    const char *end = strchr(start, '\n');
    size_t len = end ? end - start : strlen(start);

    payload->type = (char *)malloc(len + 1);
    if (!payload->type) return -2;

    strncpy(payload->type, start, len);
    payload->type[len] = '\0';

    return 0;
}

void event_handler(struct mg_connection *nc, int ev, void *ev_data, void *user_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST) {
        const char *payload_param = mg_get_header(&hm->headers, "Payload");

        if (!payload_param) {
            mg_printf(nc, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload parameter missing.\r\n");
        } else {
            payload_t payload;
            int status = parse_yaml((const char *)payload_param, strlen(payload_param), &payload);
            free(payload.type);

            if (status == 0 && strcmp(payload.type, "Create") == 0) {
                mg_printf(nc, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Create type not allowed.\r\n");
            } else if (status != 0) {
                mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError parsing YAML.\r\n");
            } else {
                mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully.\r\n");
            }
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://*:5000", event_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %d...\n", PORT);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}