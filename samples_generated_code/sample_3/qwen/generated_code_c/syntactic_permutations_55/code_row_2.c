#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char * post_values;
};

void free_connection_info(void * coninfo_cls) {
    struct ConnectionInfoStruct * con_info = (struct ConnectionInfoStruct *)coninfo_cls;
    if (NULL != con_info->post_values)
        free(con_info->post_values);
    free(con_info);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (NULL == *con_cls) {
        struct ConnectionInfoStruct *con_info;
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO; 
        con_info->post_values = NULL;
        *con_cls = (void *) con_info;

        return MHD_YES;
    }

    if (strcmp(method, "POST") == 0) {
        struct ConnectionInfoStruct *con_info = (struct ConnectionInfoStruct *)*con_cls;
        if (*upload_data_size != 0) {
            if (NULL != con_info->post_values)
                con_info->post_values = realloc(con_info->post_values,
                                                strlen(upload_data) + 1 +
                                                strlen(con_info->post_values));
            else
                con_info->post_values = malloc(strlen(upload_data) + 1);
            strcpy(&(con_info->post_values[strlen(con_info->post_values)]),
                   upload_data);
            *upload_data_size = 0;
            return MHD_YES;
        } else {
            // Handle POST request
            if (strcmp(url, "/do_login") == 0) {
                const char *response = "Login successful!";
                struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                                   (void *)response,
                                                                                   MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
                MHD_destroy_response(mhd_response);
                return ret;
            }
        }
    } else if (strcmp(method, "GET") == 0) {
        const char *response;

        if (strcmp(url, "/login") == 0) {
            response = "<html><body><form action=\"/do_login\" method=\"post\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>";
        } else if (strcmp(url, "/user_page") == 0) {
            response = "Welcome to the User Page!";
        } else if (strcmp(url, "/admin_page") == 0) {
            response = "Welcome to the Admin Page!";
        } else {
            response = "<html><body>Not found</body></html>";
            return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND,
                                     MHD_create_response_from_buffer(strlen(response),
                                                                     (void *)response,
                                                                     MHD_RESPMEM_PERSISTENT));
        }

        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                           (void *)response,
                                                                           MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_connection_info,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}