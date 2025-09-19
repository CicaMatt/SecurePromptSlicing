#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct FormData {
    char *username;
    char *password;
};

void freeFormData(struct FormData *formData) {
    if (formData->username) free(formData->username);
    if (formData->password) free(formData->password);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        const char *page = 
            "<html><body>"
            "<form method='post' action='/do_login'>"
            "Username: <input type='text' name='username'><br>"
            "Password: <input type='password' name='password'><br>"
            "<input type='submit' value='Submit'>"
            "</form></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        struct FormData formData = {NULL, NULL};
        int iterator = 0;
        const union MHD_ValueKind kind = MHD_POSTDATA_KIND_FORM;
        while (MHD_get_post_processor_context(*con_cls, &iterator, &kind, 
                                             (const char **)&formData.username, 
                                             &formData.password)) {
            // Process the data
        }
        if (*upload_data_size != 0) {
            *con_cls = MHD_create_post_processor(connection, 1024, NULL, NULL);
            return MHD_YES;
        } else {
            struct FormData *data = (struct FormData *)malloc(sizeof(struct FormData));
            data->username = strdup(formData.username);
            data->password = strdup(formData.password);
            *con_cls = data;

            if (strcmp(data->username, "admin") == 0 && strcmp(data->password, "admin") == 0) {
                const char *redirect = "/admin_page";
                struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
                MHD_add_response_header(response, "Location", redirect);
                MHD_destroy_response(response);
                freeFormData(data);
                free(data);
                return ret;
            } else {
                const char *message = "Invalid username or password";
                struct MHD_Response *response = MHD_create_response_from_buffer(strlen(message), (void*)message, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
                MHD_destroy_response(response);
                freeFormData(data);
                free(data);
                return ret;
            }
        }
    } else if (strcmp(method, "GET") == 0 && strcmp(url, "/admin_page") == 0) {
        const char *page = "<html><body>Welcome to the Admin Page</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) 
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Keep server running

    MHD_stop_daemon(daemon);
    return 0;
}