#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "mongoose.h"

#define UPLOADS_DIR "uploads"
#define MAX_REQUEST_SIZE (1024 * 1024 * 5) // 5MB

static void handle_upload(struct mg_connection *nc, struct http_message *hm) {
    const char *upload_dir = UPLOADS_DIR;
    struct mg_http_multipart_part part;
    FILE *fp = NULL;
    char file_path[256];

    if (!mg_http_is_multipart(hm)) {
        mg_send_head(nc, 400, 0, "");
        nc->flags |= MG_F_SEND_AND_CLOSE;
        return;
    }

    mkdir(upload_dir, 0755);

    while (mg_http_parse_multipart(&part, hm) == MG_OK) {
        if (part.name.len && part.filename.len) {
            snprintf(file_path, sizeof(file_path), "%s/%.*s", upload_dir, (int)part.filename.len, part.filename.p);
            fp = fopen(file_path, "wb");
            if (!fp) {
                mg_send_head(nc, 500, 0, "");
                nc->flags |= MG_F_SEND_AND_CLOSE;
                return;
            }
        }

        if (fp && part.data.len > 0) {
            fwrite(part.data.p, 1, part.data.len, fp);
        }

        if (part.is_last_part) {
            fclose(fp);
            mg_send_head(nc, 200, 0, "");
            nc->flags |= MG_F_SEND_AND_CLOSE;
            return;
        }
    }

    if (fp) fclose(fp);
    mg_send_head(nc, 400, 0, "");
    nc->flags |= MG_F_SEND_AND_CLOSE;
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->method, "POST") == 0 &&
        mg_vcmp(&hm->uri, "/upload") == 0) {
        handle_upload(nc, hm);
    } else {
        mg_serve_http(nc, hm, mg_get_options());
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", ev_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return EXIT_FAILURE;
    }

    printf("Starting web server on port 8000\n");
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return EXIT_SUCCESS;
}