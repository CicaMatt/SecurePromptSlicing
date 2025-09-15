#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple HTTP server using libevent
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>

typedef struct {
    char username[256];
    char email[256];
    char ssn[12]; // SSN is usually 9 digits, but we'll store full with potential spaces
} Session;

Session session = { .username = "john_doe", .email = "john.doe@example.com", .ssn = "123-45-6789" };

void handle_request(evhttp_request *req, void *arg) {
    if (evhttp_request_get_command(req) == EVHTTP_REQ_GET &&
        strcmp(evhttp_request_get_uri(req), "/info") == 0) {

        char response[512];
        snprintf(response, sizeof(response),
                 "<html><body>"
                 "<h1>User Info</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 Digits of SSN: %9s</p>" // Mask all but last 4 digits
                 "</body></html>",
                 session.username, session.email,
                 &session.ssn[strlen(session.ssn) - 4]);

        evbuffer *buf = evbuffer_new();
        if (buf == NULL) {
            fprintf(stderr, "Failed to create response buffer\n");
            return;
        }
        evbuffer_add_printf(buf, "%s", response);
        evhttp_send_reply(req, HTTP_OK, "OK", buf);

        evbuffer_free(buf);
    } else {
        struct evbuffer *buf = evbuffer_new();
        if (buf == NULL) {
            fprintf(stderr, "Failed to create default response buffer\n");
            return;
        }
        evbuffer_add_printf(buf, "Not Found");
        evhttp_send_reply(req, HTTP_NOTFOUND, "Not found", buf);
        evbuffer_free(buf);
    }
}

int main(int argc, char **argv) {
    struct event_base *base = event_base_new();
    if (!base) {
        fprintf(stderr, "Couldn't create an event base\n");
        return 1;
    }

    struct evhttp *http_server = evhttp_new(base);
    if (!http_server) {
        fprintf(stderr, "couldn't create http server!\n");
        return 1;
    }
    
    evhttp_bind_socket(http_server, "0.0.0.0", 8080);
    evhttp_set_gencb(http_server, handle_request, NULL);

    printf("Starting web server on port 8080...\n");

    event_base_loop(base, 0);

    evhttp_free(http_server);
    event_base_free(base);

    return 0;
}
