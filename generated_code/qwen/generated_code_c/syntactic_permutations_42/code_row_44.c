#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

static const char *username = "johndoe";
static const char *email = "john.doe@example.com";
static const char *ssn = "123-45-6789";

static void info_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        char response[256];
        snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);
        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\nContent-Length: %lu\r\n\r\n%s",
                  strlen(response), response);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", info_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}