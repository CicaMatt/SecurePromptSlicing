#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_client(int client_socket);
MYSQL* connect_db();
void close_mysql(MYSQL *conn);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
        close(new_socket);
    }

    return 0;
}

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_read = read(client_socket, buffer, sizeof(buffer));

    if (bytes_read > 0) {
        MYSQL *conn = connect_db();
        
        if (!conn) {
            return;
        }

        char lat[16], lon[16], year[6], month[4], day[4], grib_file[256];
        sscanf(buffer, "lat=%15s&lon=%15s&year=%5s&month=%3s&day=%3s&grib_file=%255s",
               lat, lon, year, month, day, grib_file);

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM weather_data "
                 "WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s';",
                 lat, lon, year, month, day, grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        } else {
            MYSQL_RES *result = mysql_store_result(conn);
            if (result) {
                MYSQL_ROW row = mysql_fetch_row(result);
                if (row && row[0]) {
                    char response[256];
                    snprintf(response, sizeof(response), "Max Temperature: %s", row[0]);
                    send(client_socket, response, strlen(response), 0);
                }
                mysql_free_result(result);
            }
        }

        close_mysql(conn);
    }
}

MYSQL* connect_db() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        close_mysql(conn);
        return NULL;
    }

    return conn;
}

void close_mysql(MYSQL *conn) {
    if (conn) {
        mysql_close(conn);
    }
}