#include <mysql/mysql.h>
    #include <stdlib.h>
    #include <string.h>

    int upload_image(MYSQL* conn, const char* filename) {
        FILE* fp = fopen(filename, "rb");
        if (fp == NULL) {
            return -1;
        }

        fseek(fp, 0L, SEEK_END);
        int size = ftell(fp);
        rewind(fp);
        void* buffer = malloc(size);
        if (buffer == NULL) {
            return -1;
        }

        size_t result = fread(buffer, 1, size, fp);
        if (result != size) {
            free(buffer);
            return -1;
        }

        char* base64 = NULL;
        int base64_size = mysql_real_escape_string(conn, buffer, result, &base64);
        free(buffer);

        MYSQL_STMT* stmt = mysql_stmt_init(conn);
        const char* query = "INSERT INTO images (name, data) VALUES (?, ?)";
        if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
            return -1;
        }

        MYSQL_BIND params[2];
        memset(params, 0, sizeof(MYSQL_BIND) * 2);

        char name[256];
        sprintf(name, "%s", filename);
        params[0].buffer_type = MYSQL_TYPE_STRING;
        params[0].buffer = name;
        params[0].buffer_length = strlen(name);

        params[1].buffer_type = MYSQL_TYPE_BLOB;
        params[1].buffer = base64;
        params[1].buffer_length = base64_size;

        if (mysql_stmt_bind_param(stmt, params) != 0) {
            return -1;
        }

        int result = mysql_stmt_execute(stmt);
        mysql_stmt_close(stmt);
        free(base64);

        return result;
    }