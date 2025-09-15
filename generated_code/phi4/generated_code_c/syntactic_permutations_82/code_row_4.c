#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

static const char *s_http_port = "8080";
static struct mg_serve_http_opts s_http_server_opts;

typedef struct {
    char *name;
} RequestPayload;

RequestPayload parse_payload(const char *payload) {
    RequestPayload req;
    req.name = NULL;

    // Assuming the payload is in the form of "name=value"
    const char *name_start = strstr(payload, "name=");
    if (name_start) {
        name_start += 5; // Move past 'name='
        const char *name_end = strchr(name_start, '&');
        if (!name_end) {
            name_end = payload + strlen(payload);
        }
        size_t len = name_end - name_start;
        req.name = (char *)malloc(len + 1);
        strncpy(req.name, name_start, len);
        req.name[len] = '\0';
    }

    return req;
}

static int s_http_handler(struct mg_connection *conn,
                          const struct mg_request_info *request_info) {

    if (strcmp(request_info->request_method, "GET") == 0 &&
        strcmp(request_info->uri, "/api") == 0) {
        
        char param_start = '?';
        char *payload_str = strchr(request_info->query_string, param_start);
        if (!payload_str) {
            mg_printf(conn,
                      "HTTP/1.1 400 Bad Request\r\n"
                      "Content-Type: text/plain\r\n"
                      "\r\n"
                      "Missing payload parameter.");
            return MG_TRUE;
        }

        payload_str++; // Move past the '?'
        RequestPayload req = parse_payload(payload_str);

        if (req.name) {
            mg_printf(conn,
                      "HTTP/1.1 200 OK\r\n"
                      "Content-Type: application/json\r\n"
                      "\r\n"
                      "{ \"name\": \"%s\" }", req.name);
            free(req.name);
        } else {
            mg_printf(conn,
                      "HTTP/1.1 400 Bad Request\r\n"
                      "Content-Type: text/plain\r\n"
                      "\r\n"
                      "Invalid payload.");
        }

    } else {
        mg_serve_http(conn, (struct http_message *)request_info, s_http_server_opts);
    }
    
    return MG_TRUE;
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, s_http_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current dir
    s_http_server_opts.enable_directory_listing = "yes";

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}
