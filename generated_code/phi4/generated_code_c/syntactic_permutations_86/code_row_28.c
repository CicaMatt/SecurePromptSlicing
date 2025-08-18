#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PORT 8080

void handle_request(int client_socket, MYSQL *conn) {
    char request[1024];
    read(client_socket, request, sizeof(request));

    char latitude[50], longitude[50], year[5], month[3];
    sscanf(request, "GET /api/temperature_for_location?latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%s", latitude, longitude, year, month);

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s",
             latitude, longitude, year, month);

    if (mysql_query(conn, query)) {
        char *error_msg = mysql_error(conn);
        write(client_socket, error_msg, strlen(error_msg));
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row) {
            write(client_socket, row[0], strlen(row[0]));
        } else {
            char *no_data_msg = "No data found";
            write(client_socket, no_data_msg, strlen(no_data_msg));
        }
        mysql_free_result(result);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Initialize MySQL connection
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "password", "weather_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Create socket and bind
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
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
    
    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        handle_request(new_socket, conn);

        mysql_close(conn);
    }

    return 0;
}