#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *username = "johndoe";
static const char *email = "john.doe@example.com";
static const char *ssn_last4 = "1234";

void info(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
            mg_printf(nc, "<html><body>");
            mg_printf(nc, "<h1>User Information</h1>");
            mg_printf(nc, "<p>Username: %s</p>", username);
            mg_printf(nc, "<p>Email: %s</p>", email);
            mg_printf(nc, "<p>Last 4 digits of SSN: %s</p>", ssn_last4);
            mg_printf(nc, "</body></html>");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    const char *options[] = {"listening_port", "8000", NULL};

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, options[1], info);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;
}