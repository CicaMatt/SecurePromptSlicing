#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        // Extract parameters from request
        char latitude[10], longitude[10], year[5], month[3], day[3], grib_file[100];
        
        sscanf(buffer, "GET /?latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
               latitude, longitude, year, month, day, grib_file);

        // Connect to MySQL
        MYSQL *conn;
        conn = mysql_init(NULL);
        
        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            perror("Database connection failed");
            close(client_socket);
            return;
        }

        // Prepare query
        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s "
                 "AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
                 latitude, longitude, year, month, day, grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            MYSQL_RES *result = mysql_store_result(conn);
            if (result) {
                MYSQL_ROW row = mysql_fetch_row(result);
                char response[256];
                snprintf(response, sizeof(response), "Max Temperature: %s\n", row ? row[0] : "N/A");
                send(client_socket, response, strlen(response), 0);
                mysql_free_result(result);
            }
        }

        mysql_close(conn);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to PORT
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);
    }

    return 0;
}