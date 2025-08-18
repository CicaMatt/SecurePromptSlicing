#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = mg_get_http_var(&hm->body, "username", 50);
    const char *email = mg_get_http_var(&hm->body, "email", 100);
    const char *ssn = mg_get_http_var(&hm->body, "ssn", 12);

    char last_four_ssn[5];
    strncpy(last_four_ssn, ssn + strlen(ssn) - 4, 4);
    last_four_ssn[4] = '\0';

    char response[256];
    snprintf(response, sizeof(response),
             "Username: %s<br>Email: %s<br>Last 4 of SSN: %s",
             username ? username : "Not set",
             email ? email : "Not set",
             last_four_ssn);

    mg_http_send_head(nc, 200, strlen(response), "Content-Type: text/html");
    mg_printf(nc, "%s", response);
}

static void event_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/info") == 0) {
        info(nc, hm);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8000", event_handler);
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