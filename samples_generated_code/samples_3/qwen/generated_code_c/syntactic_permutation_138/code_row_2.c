#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <sqlite3.h>

#define PORT 8888

struct connection_info_struct {
    char *answerstring;
    int answercode;
};

int check_moderator(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc == 1 && strcmp(argv[0], "1") == 0) {
        printf("User is a moderator.\n");
        return 0;
    } else {
        printf("User is not a moderator.\n");
        return 1;
    }
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info;
    int ret;

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (con_info == NULL)
            return MHD_NO;
        con_info->answerstring = NULL;
        *con_cls = con_info;
        return MHD_YES;
    }

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return MHD_NO;
    }

    const char* data = "SELECT is_moderator FROM users WHERE user_id=1";
    rc = sqlite3_exec(db, data, check_moderator, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to select data: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);

    con_info->answerstring = strdup("Query executed");
    con_info->answercode = MHD_HTTP_OK;

    ret = MHD_queue_response(connection, con_info->answercode,
                              MHD_create_response_from_buffer(strlen(con_info->answerstring),
                                                              (void*)con_info->answerstring, MHD_RESPMEM_MUST_FREE));

    free(con_info);
    *con_cls = NULL;
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}