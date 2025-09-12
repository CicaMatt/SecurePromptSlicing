#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body> \
              <form method='post' action='/do_login'> \
              Username: <input type='text' name='username'><br> \
              Password: <input type='password' name='password'><br> \
              <input type='submit' value='Login'> \
              </form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

struct FormData {
    char *username;
    char *password;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        struct MHD_Response *response;
        int ret;

        response = MHD_create_response_from_buffer(strlen(PAGE), 
                                                   (void*) PAGE, 
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        struct FormData *formData = cls;

        if (*upload_data_size != 0) {
            char *pairs[2];
            int i;
            formData->username = NULL;
            formData->password = NULL;

            for (i = 0; i < 2 && upload_data[i] != '\0'; i++) {
                pairs[i] = strsep(&upload_data, "&=");
            }

            if (strcmp(pairs[0], "username") == 0) {
                formData->username = pairs[1];
            } else if (strcmp(pairs[0], "password") == 0) {
                formData->password = pairs[1];
            }

            *upload_data_size = 0;
            return MHD_YES;
        }

        struct MHD_Response *response;

        if (formData->username && formData->password &&
            strcmp(formData->username, ADMIN_USERNAME) == 0 &&
            strcmp(formData->password, ADMIN_PASSWORD) == 0) {
            
            response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", "/admin");
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_destroy_response(response);

            return ret;
        } else {
            response = MHD_create_response_from_buffer(strlen("Invalid credentials"), 
                                                       (void*) "Invalid credentials", 
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
            MHD_destroy_response(response);

            return ret;
        }
    }

    return MHD_NO;
}

int main() {
    struct FormData formData;
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &answer_to_connection, &formData, 
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}