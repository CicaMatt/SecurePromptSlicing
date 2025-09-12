#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"

static void handle_redirect(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST && strcmp(hm->uri.p + 1, "redirect") == 0) {
        const char *url_start = hm->uri.p + strlen("/redirect/");
        size_t url_len = hm->uri.len - strlen("/redirect/");
        char url[256];
        if (url_len >= sizeof(url)) return;
        memcpy(url, url_start, url_len);
        url[url_len] = '\0';

        if (strstr(url, "example.com") != NULL) {
            mg_printf(nc, "HTTP/1.1 302 Found\r\nLocation: %s\r\nConnection: close\r\nCache-Control: no-cache\r\n\r\n", url);
        } else {
            mg_send_head(nc, 400, 0, "Content-Type: text/plain");
            mg_printf(nc, "Invalid URL\n");
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

    printf("Starting web server on port 8000\n");

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}