#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>Check Mod</body></html>"
#define USERNAME "admin"
#define PASSWORD "password"

int check_mod(const char* username, const char* password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    const char* response;
    struct MHD_Response *mhd_response;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (0 != *upload_data_size) {
        char username[128] = "";
        char password[128] = "";
        sscanf(upload_data, "username=%127[^&]&password=%127s", username, password);
        response = check_mod(username, password) ? "true" : "false";
        *upload_data_size = 0;
    } else {
        return MHD_NO;
    }

    mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}