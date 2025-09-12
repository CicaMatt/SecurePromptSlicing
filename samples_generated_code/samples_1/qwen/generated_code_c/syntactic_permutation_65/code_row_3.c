#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libwebsockets.h>

#define MAX_PAYLOAD 1024

struct upload_session {
    FILE *file;
};

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    struct upload_session *session = (struct upload_session *)user;
    char buffer[MAX_PAYLOAD + 1];
    const char *filename;

    switch (reason) {
        case LWS_CALLBACK_HTTP:
            if (lws_hdr_total_length(wsi, WSI_TOKEN_POST_FILENAME)) {
                filename = lws_hdr_ptr(wsi, WSI_TOKEN_POST_FILENAME);
                mkdir("uploads", 0755);
                session->file = fopen(strcat((char *)"uploads/", filename), "wb");
                if (!session->file) {
                    lwsl_err("Failed to open file for writing\n");
                    return -1;
                }
            } else {
                lws_serve_http_file(wsi, "upload.html", NULL, 0);
            }
            break;

        case LWS_CALLBACK_RECEIVE_HTTP:
            fwrite(in, len, 1, session->file);
            break;

        case LWS_CALLBACK_HTTP_FILE_COMPLETION:
            if (session->file) {
                fclose(session->file);
                session->file = NULL;
            }
            lws_return_http_status(wsi, HTTP_STATUS_OK, "Upload complete");
            break;

        default:
            break;
    }

    return 0;
}

static struct lws_protocols protocols[] = {
    {"http-only", callback_http, sizeof(struct upload_session), MAX_PAYLOAD},
    {NULL, NULL, 0, 0}
};

int main(int argc, char **argv) {
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));

    info.port = 7681;
    info.protocols = protocols;

    struct lws_context *context = lws_create_context(&info);
    if (!context) {
        lwsl_err("lws init failed\n");
        return -1;
    }

    printf("Starting server...\n");

    while (1) {
        lws_service(context, 0);
    }

    lws_context_destroy(context);

    return 0;
}