#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

void handle_api(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *payload_query = mg_get_http_var(&hm->query_string, "payload");
        
        if (payload_query != NULL) {
            // Simulate loading payload into a dictionary
            // Here we assume the payload is in the format "name=John"
            const char *name_value = strstr(payload_query, "name=");
            if (name_value != NULL) {
                name_value += 5; // Move pointer to after "name="
                char name[100];
                strncpy(name, name_value, strchr(name_value, '&') - name_value);
                
                mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n");
                mg_printf(nc, "%s", name);
            } else {
                mg_send_head(nc, 400, 0, "Content-Type: text/plain");
                mg_printf(nc, "%s", "Bad Request");
            }
        } else {
            mg_send_head(nc, 400, 0, "Content-Type: text/plain");
            mg_printf(nc, "%s", "Missing payload parameter");
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

    s_http_server_opts.document_root = ".";  // Serve current directory
    printf("Starting server on port 8000\n");

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL) {
        ;
    }
    
    mg_mgr_free(&mgr);

    return 0;
}