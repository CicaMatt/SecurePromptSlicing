#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>\
<form method='post' action='/do_login'>\
    Username: <input type='text' name='username'><br/>\
    Password: <input type='password' name='password'><br/>\
    <input type='submit' value='Login'>\
</form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(PAGE), 
                                                   (void*) PAGE, 
                                                   MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        const char *username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
        const char *password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen("Redirecting..."), 
                                                       (void*) "Redirecting...", 
                                                       MHD_RESPMEM_PERSISTENT);
            MHD_add_response_header(response, "Location", "/admin_page");
            int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
            MHD_destroy_response(response);
            return ret;
        } else {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen("Invalid credentials"), 
                                                       (void*) "Invalid credentials", 
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
            MHD_destroy_response(response);
            return ret;
        }
    } else if (strcmp(url, "/admin_page") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("<html><body>Admin Page</body></html>"), 
                                                   (void*) "<html><body>Admin Page</body></html>", 
                                                   MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}