#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

typedef struct {
    char username[50];
    char message[256];
} PostData;

int insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic.
    printf("Inserting into DB: Username=%s, Message=%s\n", username, message);
    return 0; // Return 0 on success
}

void view_message_handler(struct mg_connection *conn, void *data) {
    (void)data;
    char response[1024] = "Messages:\n";
    // Placeholder for fetching messages from the database.
    strcat(response, "User1: Hello\n");
    strcat(response, "User2: World\n");
    mg_send_head(conn, 200, strlen(response), "Content-Type: text/plain\r\n");
    mg_printf_data(conn, "%s", response);
}

int post_message_handler(struct mg_connection *conn, void *cbdata) {
    (void)cbdata;
    struct http_message *hm = mg_get_request_info(conn);

    if (mg_vcmp(&hm->uri, "/post") == 0 && hm->method == MG_EV_HTTP_REQUEST) {
        PostData post_data = { .username = "", .message = "" };
        
        char key[50], value[256];
        for (struct mg_http_header *h = hm->http_headers; h != NULL; h = h->next) {
            if (strcmp(h->name, "username") == 0) {
                strncpy(key, h->name, sizeof(key));
                strncpy(value, h->value, sizeof(value));
                strncpy(post_data.username, value, sizeof(post_data.username));
            }
            else if (strcmp(h->name, "message") == 0) {
                strncpy(key, h->name, sizeof(key));
                strncpy(value, h->value, sizeof(value));
                strncpy(post_data.message, value, sizeof(post_data.message));
            }
        }

        insert_user_message_in_db(post_data.username, post_data.message);
        
        mg_serve_http(conn, (struct http_message *)NULL, "text/plain", 200,
                      NULL, "Location: /\r\n");
    }
    return MG_TRUE;
}

static struct mg_connection *nc = NULL;

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&conn->uri, "/post") == 0)
                post_message_handler(conn, NULL);
            else
                view_message_handler(conn, NULL);
            return MG_TRUE;

        case MG_EV_ACCEPTED:
            nc = conn;
            break;
    }
    return MG_FALSE;
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);

    const char *addr = "http://localhost:8080";
    struct mg_connection *nc = mg_bind(&mgr, addr, ev_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on %s\n", addr);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}
