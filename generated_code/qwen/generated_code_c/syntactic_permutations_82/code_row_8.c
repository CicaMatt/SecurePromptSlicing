#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define MAX_PAYLOAD_SIZE 1024

static void handle_api(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *query = hm->query.p ? mg_url_decode(hm->query.p, hm->query.len, NULL, 0, 1) : "";
        
        char payload[MAX_PAYLOAD_SIZE] = {0};
        mg_get_http_var(query, strlen(query), "payload", payload, sizeof(payload));

        // Simple parsing of the payload as a dictionary
        char *name_value_start = strstr(payload, "\"name\":\"");
        if (name_value_start != NULL) {
            name_value_start += 8; // Move past "\"name\":\""
            char *name_value_end = strchr(name_value_start, '"');
            if (name_value_end != NULL) {
                int name_length = name_value_end - name_value_start;
                char name[name_length + 1];
                strncpy(name, name_value_start, name_length);
                name[name_length] = '\0';
                
                mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n%s", name);
                return;
            }
        }

        mg_send_head(nc, 400, 0, "Content-Type: text/plain");
        mg_printf(nc, "Bad Request");
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

    printf("Starting server on port 8000\n");
    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {}

    mg_mgr_free(&mgr);
    return 0;
}