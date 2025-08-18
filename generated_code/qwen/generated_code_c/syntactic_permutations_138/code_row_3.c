#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "test_db"

struct connection_info_struct {
    int conref;
    char *data;
};

MYSQL* connect_to_database() {
    MYSQL *con = mysql_init(NULL);
    if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    return con;
}

int check_if_moderator(MYSQL *con, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -1;
    }

    int is_moderator = 0;
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(result);
    return is_moderator;
}

void *create_response(void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info = cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        *con_cls = con_info;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        con_info->data = strdup(upload_data);
        *upload_data_size = 0;
        return MHD_YES;
    }

    MYSQL *con = connect_to_database();
    int is_moderator = check_if_moderator(con, url + 1); // Assuming URL format /username
    mysql_close(con);

    char response[256];
    snprintf(response, sizeof(response), "{\"is_moderator\": %d}", is_moderator);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                        (void*)response,
                                                                        MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free(con_info->data);
    free(con_info);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &create_response, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}