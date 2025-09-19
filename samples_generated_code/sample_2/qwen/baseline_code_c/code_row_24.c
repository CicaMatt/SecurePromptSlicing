#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_user_info = "{\"username\": \"johndoe\", \"email\": \"john.doe@example.com\", \"ssn_last_4\": \"1234\"}";

static void fn(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: close\r\n\r\n%s", s_user_info);
        } else {
            mg_send_head(nc, 404, 0, "");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    const char *opts[] = {"listening_port", "8000", NULL};

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, opts[1], fn);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    return 0;
}