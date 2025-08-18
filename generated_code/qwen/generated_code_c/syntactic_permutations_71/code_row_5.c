#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "mongoose.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void upload_handler(struct mg_connection *nc, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;
        const char *content_type = mg_get_http_header(hm, "Content-Type");
        if (mg_vcmp(&hm->method, "POST") == 0 && content_type != NULL &&
            strstr(content_type, "multipart/form-data")) {
            struct mg_file_upload_state fu_state;
            memset(&fu_state, 0, sizeof(fu_state));
            for (;;) {
                const char *filename = mg_get_http_var(&hm->body, "name", 100);
                if (mg_parse_multipart(&hm->body, &fu_state) == NULL) break;
                FILE *fp = fopen(filename, "wb");
                fwrite(fu_state.data.ptr, 1, fu_state.data.len, fp);
                fclose(fp);
            }
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Length: 23\r\n\r\nFile uploaded successfully!");
        } else {
            const char *form = "<html><body>"
                               "<h1>Upload File</h1>"
                               "<form method='POST' enctype='multipart/form-data'>"
                               "File: <input type='file' name='name'><br>"
                               "<input type='submit' value='Upload'>"
                               "</form></body></html>";
            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Length: %lu\r\n"
                        "Content-Type: text/html\r\n\r\n%s",
                        strlen(form), form);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, upload_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}