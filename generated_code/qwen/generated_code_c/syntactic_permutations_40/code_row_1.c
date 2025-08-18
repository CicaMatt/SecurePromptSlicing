#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct UserData {
    char username[50];
    char email[100];
    char ssn_last4[5];
};

void info(struct mg_connection *nc, struct http_message *hm) {
    const char *username = mg_get_http_var(&hm->body, "username", 50);
    const char *email = mg_get_http_var(&hm->body, "email", 100);
    const char *ssn_last4 = mg_get_http_var(&hm->body, "ssn_last4", 5);

    if (username != NULL && email != NULL && ssn_last4 != NULL) {
        struct UserData userData;
        strncpy(userData.username, username, sizeof(userData.username));
        strncpy(userData.email, email, sizeof(userData.email));
        strncpy(userData.ssn_last4, ssn_last4, sizeof(userData.ssn_last4));

        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
        mg_printf(nc, "<html><body>");
        mg_printf(nc, "<h1>User Information</h1>");
        mg_printf(nc, "<p>Username: %s</p>", userData.username);
        mg_printf(nc, "<p>Email: %s</p>", userData.email);
        mg_printf(nc, "<p>SSN Last 4: %s</p>", userData.ssn_last4);
        mg_printf(nc, "</body></html>");
    } else {
        mg_send_head(nc, 400, strlen("Bad Request"), "Content-Type: text/plain");
        mg_printf(nc, "Bad Request");
    }
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    if (ev == MG_EV_HTTP_REQUEST) {
        if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method.p[0] == 'G') {
            info(nc, hm);
        } else {
            mg_send_head(nc, 404, strlen("Not Found"), "Content-Type: text/plain");
            mg_printf(nc, "Not Found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", ev_handler);
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