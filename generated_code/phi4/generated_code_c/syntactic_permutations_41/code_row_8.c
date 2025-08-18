#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"

typedef struct {
    char username[50];
    char email[100];
    char ssn[15]; // SSN format: XXX-XX-XXXX, so we need to store the whole thing temporarily.
} UserInfo;

UserInfo getUserInfo() {
    UserInfo info;
    strcpy(info.username, "JohnDoe");
    strcpy(info.email, "johndoe@example.com");
    strcpy(info.ssn, "123-45-6789"); // Example SSN
    return info;
}

static void ev_handler(struct mg_connection *conn, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        UserInfo info = getUserInfo();
        
        char response[256];
        snprintf(response, sizeof(response), 
                 "Username: %s\nEmail: %s\nSSN (last 4 digits): %.4s",
                 info.username, info.email, &info.ssn[7]);

        mg_printf(conn,
                  "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/plain\r\n"
                  "Connection: close\r\n"
                  "\r\n"
                  "%s", response);
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
    printf("Starting web server on port %d\n", 8080);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
}


This code uses the Mongoose library to handle HTTP requests. You need to have Mongoose installed and linked properly when compiling this program. Compile with:


gcc -o webapp webapp.c -lmongoose


Run the compiled program:


./webapp


Visit `http://localhost:8080/info` in a browser or use curl from the terminal to see the output.