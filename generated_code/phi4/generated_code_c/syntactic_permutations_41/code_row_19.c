#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static struct mg_serve_http_opts shttp;

void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        const char *email = "user@example.com";
        const char *ssn_last_4 = "1234";

        char response[1024];
        snprintf(response, sizeof(response),
                 "<html><body>"
                 "<h1>Info Page</h1>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 Digits of SSN: %s</p>"
                 "</body></html>", 
                 email, ssn_last_4);
        
        mg_send_head(nc, 200, strlen(response), "Content-Type: text/html");
        mg_printf(nc, "%s", response);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8080", ev_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    shttp.document_root = ".";

    printf("Starting web server on port 8080...\n");
    
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
}


To compile and run this code, you need to have the Mongoose library installed. You can typically compile it using a command like:


gcc -o my_app my_app.c -lmongoose
./my_app


Ensure that Mongoose is properly linked in your compilation command.