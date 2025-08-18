#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define PORT 8080

int insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function for demonstration purposes.
    printf("Inserting message from %s: %s\n", username, message);
    return 1; // Assume success
}

static void event_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST && hm->method_num == MGHTTP_METHOD_POST) {
        char username[100], message[256];
        
        struct mg_str key;
        const char *value;
        
        for (int i = 0; i < hm->num_headers; ++i) {
            if (strcmp(hm->headers[i].name, "username") == 0) {
                key = hm->headers[i].value;
                strncpy(username, (const char *)key.ptr, sizeof(username));
                username[sizeof(username) - 1] = '\0';
            }
            
            if (strcmp(hm->headers[i].name, "message") == 0) {
                key = hm->headers[i].value;
                strncpy(message, (const char *)key.ptr, sizeof(message));
                message[sizeof(message) - 1] = '\0';
            }
        }

        insert_user_message_in_db(username, message);

        mg_send_head(nc, 302, 0, "text/plain", "Location: /");
    } else if (ev == MG_EV_HTTP_REQUEST && strcmp(hm->uri.p, "/") == 0) {
        const char *html = 
            "<html><body>"
            "<h1>Messages</h1>"
            "<ul>"
            // Placeholder for messages
            "<li>User: John Doe - Message: Hello World!</li>" // Example message
            "</ul>"
            "<form action=\"/post\" method=\"POST\">"
            "Username: <input type=\"text\" name=\"username\"><br>"
            "Message: <textarea name=\"message\"></textarea><br>"
            "<input type=\"submit\" value=\"Submit\">"
            "</form>"
            "</body></html>";

        mg_printf(nc, "%s", html);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://0.0.0.0:%d/", event_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %d\n", PORT);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}


To compile and run this code, you will need the Mongoose library. You can install it from [mongoose.org](https://github.com/cesanta/mongoose). Then use the following command to compile:


gcc -o server your_file.c -lmongoose
./server


This code sets up a simple HTTP server using Mongoose, handling POST requests at `/post` and displaying messages on the root route.