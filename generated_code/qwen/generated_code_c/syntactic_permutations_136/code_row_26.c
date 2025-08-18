#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body>Result: %s</body></html>"
#define USERNAME "admin"
#define PASSWORD "password"

int check_mod(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/check_mod?username=")) {
        const char *query = strchr(url, '?') + 1;
        const char *username = strstr(query, "username=");
        const char *password = strstr(query, "&password=");
        
        if (username && password) {
            username += strlen("username=");
            password += strlen("&password=");
            
            char *end_password = strchr((char*)password, '&');
            if (end_password) *end_password = '\0';

            int result = check_mod(username, password);
            const char *response = result ? "true" : "false";

            char buffer[256];
            snprintf(buffer, sizeof(buffer), PAGE, response);

            struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(buffer),
                                                                               (void*)buffer,
                                                                               MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
            MHD_destroy_response(response_obj);
            return ret;
        }
    }

    return MHD_NO;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              8888, NULL, NULL, &answer_to_connection,
                              NULL, MHD_OPTION_END);
    
    if (NULL == daemon) return 1;
    
    getchar();
    
    MHD_stop_daemon(daemon);
    return 0;
}