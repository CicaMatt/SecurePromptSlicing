#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char * get_name_field(const char *content, size_t length) {
    const char *field = "name=";
    size_t field_len = strlen(field);
    const char *start = memmem(content, length, field, field_len);
    
    if (start == NULL) return NULL;
    
    start += field_len;
    const char *end = memchr(start, '&', length - (start - content));
    
    if (end == NULL) end = start + strcspn(start, " \r\n");
    
    size_t name_len = end - start;
    char *name = malloc(name_len + 1);
    strncpy(name, start, name_len);
    name[name_len] = '\0';
    
    return name;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0) return MHD_NO;
    
    const char *name = get_name_field(upload_data, *upload_data_size);
    if (name == NULL) return MHD_NO;
    
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(name), 
                                               (void*) name, 
                                               MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    
    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    
    getchar();
    
    MHD_stop_daemon(daemon);
    return 0;
}