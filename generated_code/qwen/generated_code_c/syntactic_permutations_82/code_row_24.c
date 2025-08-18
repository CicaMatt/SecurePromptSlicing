#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static void handle_api(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        const char *payload = mg_get_http_var(&hm->query_string, "payload");
        
        if (payload != NULL) {
            // Simple parsing of payload assuming it's in the form "name=value"
            const char *name_start = strstr(payload, "name=");
            if (name_start != NULL) {
                name_start += 5; // Move past "name="
                const char *name_end = strchr(name_start, '&');
                size_t name_len = (name_end == NULL) ? strlen(name_start) : (size_t)(name_end - name_start);
                char name[1024];
                strncpy(name, name_start, name_len);
                name[name_len] = '\0';
                
                mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n%s", name);
            } else {
                mg_send_head(nc, 400, 0, "Content-Type: text/plain\r\n");
                mg_printf(nc, "Missing 'name' in payload");
            }
        } else {
            mg_send_head(nc, 400, 0, "Content-Type: text/plain\r\n");
            mg_printf(nc, "Payload parameter not found");
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
        return EXIT_FAILURE;
    }

    printf("Starting server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}