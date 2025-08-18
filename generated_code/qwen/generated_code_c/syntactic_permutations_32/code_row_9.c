#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static void handle_redirect(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST) {
        const char *uri = hm->uri.p + strlen("/redirect/");
        size_t uri_len = hm->uri.len - strlen("/redirect/");
        char url[1024];
        strncpy(url, uri, uri_len);
        url[uri_len] = '\0';

        if (strstr(url, "example.com") != NULL) {
            mg_http_send_redirect(nc, 302, "%s", "Location: ");
            mg_printf(nc, "%.*s\r\n", (int) uri_len, uri);
            mg_send_head(nc, 302, 0, "");
        } else {
            mg_send_head(nc, 400, 0, "");
            mg_printf(nc, "Invalid URL");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", handle_redirect);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting server on port 8000\n");

    while (mg_mgr_poll(&mgr, 1000) == MG_EV_POLL);

    mg_mgr_free(&mgr);
    return 0;
}