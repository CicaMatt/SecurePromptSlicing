#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8080

struct connection_info_struct {
    char *answerstring;
    size_t answer_size;
};

const char *ask_db() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT 'Hello, World!'")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s \n", row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return "Query executed successfully";
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_ref) {
    static int aptr;
    struct connection_info_struct *con_info = cls;

    if (NULL == con_info->answerstring) {
        con_info->answerstring = (char *) ask_db();
        con_info->answer_size = strlen(con_info->answerstring);
    }

    if (*upload_data_size != 0) {
        return MHD_NO;
    }

    *con_ref = NULL;

    struct MHD_Response *response = MHD_create_response_from_buffer(
            con_info->answer_size, (void *) con_info->answerstring, MHD_RESPMEM_MUST_FREE);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;
    struct connection_info_struct *con_info;

    con_info = malloc(sizeof(struct connection_info_struct));
    if (NULL == con_info)
        return 1;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, (void *) con_info, MHD_OPTION_END);
    if (NULL == daemon) {
        free(con_info);
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    free(con_info);

    return 0;
}