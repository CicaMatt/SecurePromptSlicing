#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct ConnectionInfoStruct {
    int connectiontype;
    struct MHD_PostProcessor *postprocessor;
};

const char *getPrice(float quantity) {
    float pricePerUnit = 10.0; // Example price per unit
    float totalPrice = quantity * pricePerUnit;
    static char result[50];
    snprintf(result, sizeof(result), "{\"total_price\": %.2f}", totalPrice);
    return result;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *con_info = cls;

    if (NULL == con_info->postprocessor) {
        con_info->connectiontype = 0;
        if (0 != strcmp(method, "POST")) return MHD_NO;
        const char *clen = MHD_lookup_connection_value(connection,
                                                        MHD_HEADER_KIND,
                                                        MHD_HTTP_HEADER_CONTENT_LENGTH);
        if (!clen) return MHD_NO;
        int len = atoi(clen);
        con_info->postprocessor = MHD_create_post_processor(connection, 1024, NULL, NULL);
        con_info->connectiontype = 1;
    }

    MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
    if (*upload_data_size != 0) {
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char* quantity_str = MHD_lookup_connection_value(connection,
                                                            MHD_POSTDATA_KIND,
                                                            "quantity");
    float quantity = quantity_str ? atof(quantity_str) : 0.0;

    const char *response = getPrice(quantity);
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}