#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

typedef struct {
    char *name;
    char *email;
    char *ssn;
} UserSession;

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;

        // Check if the request is a GET to /info
        if (mg_vcmp(&hm->uri, "/info") == 0 && mg_get_http_method(hm) == HTTP_METHOD_GET) {
            UserSession session;
            session.name = "John Doe";
            session.email = "john.doe@example.com";
            session.ssn = "123-45-6789";

            const char *response_body = 
                "Name: " + (session.name ? session.name : "") + "\n"
                "Email: " + (session.email ? session.email : "") + "\n"
                "SSN: " + (session.ssn ? session.ssn : "");

            mg_printf(nc, 
                      "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/plain\r\n"
                      "Connection: close\r\n"
                      "\r\n"
                      "%s", response_body);
        } else {
            mg_send_http_error(nc, 404, "Not Found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:8080", ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on http://0.0.0.0:8080/\nPress Enter to stop\n");

    getchar();

    mg_mgr_free(&mgr);
    return 0;
}


To compile and run the above code, you need the Mongoose library. You can install it using a package manager or download it from its official website. Here's an example of how you might compile it:


gcc -o webapp main.c -lmongoose
./webapp


Ensure that `mongoose.h` and `libmongoose.a` (or appropriate compiled version) are available in your include path and library search path, respectively.