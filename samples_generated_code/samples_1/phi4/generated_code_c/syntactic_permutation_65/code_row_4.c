#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libmicrohttpd.h"

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    int ret;
    if (strcmp(method, "POST") == 0 && strcmp(url, "/upload") == 0) {
        FILE *file = fopen("./uploads/uploaded_file.pdf", "wb");
        if (!file) return MHD_NO;

        while (*upload_data_size > 0) {
            fwrite(upload_data, sizeof(char), *upload_data_size, file);
            upload_data += *upload_data_size;
            *upload_data_size -= *upload_data_size;
        }
        fclose(file);

        const char *response = "File uploaded successfully!";
        struct MHD_Response *mhd_response =
            MHD_create_response_from_buffer(strlen(response),
                                            (void *) response,
                                            MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

    } else if (strcmp(method, "GET") == 0 && strcmp(url, "/upload_form.html") == 0) {
        const char *html =
            "<form method='POST' enctype='multipart/form-data' action='/upload'>"
            "<input type='file' name='uploaded_file' accept='.pdf'/>"
            "<button type='submit'>Upload PDF</button>"
            "</form>";
        struct MHD_Response *mhd_response =
            MHD_create_response_from_buffer(strlen(html),
                                            (void *) html,
                                            MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

    } else {
        const char *response = "404 Not Found";
        struct MHD_Response *mhd_response =
            MHD_create_response_from_buffer(strlen(response),
                                            (void *) response,
                                            MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, mhd_response);
        MHD_destroy_response(mhd_response);
    }
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for user to press Enter

    MHD_stop_daemon(daemon);
    return 0;
}


Note: Make sure the `libmicrohttpd` library is installed and linked during compilation. This can be done using a command like:

gcc -o server your_program.c $(pkg-config --cflags --libs libmicrohttpd)

Ensure the directory `uploads` exists in the same location as your compiled executable to store uploaded PDFs.