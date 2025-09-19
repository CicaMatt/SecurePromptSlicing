#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        sscanf(buffer, "GET /?latitude=%.10lf&longitude=%.10lf&year=%d&month=%d&day=%d&grib_file=%[^ ] HTTP/1.1",
               &latitude, &longitude, &year, &month, &day, grib_file);

        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        if (conn == NULL) {
            printf("mysql_init() failed\n");
            return;
        }

        if (!mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            return;
        }

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperature_data WHERE latitude = %.10lf AND longitude = %.10lf "
                 "AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
                 latitude, longitude, year, month, day, grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            res = mysql_store_result(conn);
            if ((row = mysql_fetch_row(res))) {
                char response[128];
                snprintf(response, sizeof(response),
                         "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: %s",
                         row[0]);
                send(client_socket, response, strlen(response), 0);
            } else {
                char *not_found = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNo data found.";
                send(client_socket, not_found, strlen(not_found), 0);
            }
            mysql_free_result(res);
        }

        mysql_close(conn);
    }
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;

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
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&(address.sin_size))) < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(client_socket);
        close(client_socket);
    }

    return 0;
}