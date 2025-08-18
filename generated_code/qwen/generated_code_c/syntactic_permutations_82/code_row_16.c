#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char *name;
} Payload;

void parse_payload(const char *payload, Payload *parsed) {
    const char *prefix = "\"name\":\"";
    const char *start = strstr(payload, prefix);
    if (start != NULL) {
        start += strlen(prefix);
        const char *end = strchr(start, '"');
        if (end != NULL) {
            size_t len = end - start;
            parsed->name = malloc(len + 1);
            strncpy(parsed->name, start, len);
            parsed->name[len] = '\0';
        }
    }
}

static void handle_api(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST) {
        if (mg_vcmp(&hm->uri, "/api") == 0 && hm->method.len == 3 && memcmp(hm->method.p, "GET", 3) == 0) {
            char payload[MAX_PAYLOAD_SIZE];
            mg_http_get_var(&hm->query_string, "payload", payload, sizeof(payload));
            
            Payload parsed = {NULL};
            parse_payload(payload, &parsed);
            
            if (parsed.name != NULL) {
                mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n%s", parsed.name);
                free(parsed.name);
            } else {
                mg_send_head(nc, 400, 0, "");
            }
        } else {
            mg_send_head(nc, 404, 0, "");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", handle_api);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port 8000\n");
    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    mg_mgr_free(&mgr);
    return 0;
}