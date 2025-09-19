#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static const char *s_username = "johndoe";
static const char *s_email = "john.doe@example.com";
static const char *s_ssn = "123456789";

static void info(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            char response[128];
            snprintf(response, sizeof(response),
                     "Username: %s\nEmail: %s\nLast 4 of SSN: %.*s",
                     s_username, s_email, 4, s_ssn + strlen(s_ssn) - 4);
            mg_send_head(nc, 200, (int) strlen(response), "Content-Type: text/plain");
            mg_send(nc, response, strlen(response));
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", info);
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