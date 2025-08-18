#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "mongoose.h"

#define UPLOADS_DIR "./uploads/"

void handle_upload(struct mg_connection *nc, int ev, void *p) {
    struct mg_http_message *hm = (struct mg_http_message *) p;
    if (ev == MG_EV_HTTP_PART_BEGIN && hm->is_multipart) {
        mkdir(UPLOADS_DIR, 0755);
    } else if (ev == MG_EV_HTTP_MULTIPART_BODY) {
        FILE *fp;
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s%s", UPLOADS_DIR, hm->multipart.name.ptr);
        fp = fopen(file_path, "ab");
        if (fp != NULL) {
            fwrite(hm->body.ptr, 1, hm->body.len, fp);
            fclose(fp);
        }
    } else if (ev == MG_EV_HTTP_PART_END) {
        mg_http_reply(nc, 200, "", "File uploaded successfully\n");
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://localhost:8000", handle_upload, NULL);
    printf("Starting server on http://localhost:8000\n");
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}