#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void handle_request(int client_socket, MYSQL *conn) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    
    if (valread > 0) {
        // Assuming the request is a simple GET with query parameters
        char lat[20], lon[20], year[5], month[3], day[3], grib_file[100];
        
        sscanf(buffer, "GET /?lat=%[^&]&lon=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
               lat, lon, year, month, day, grib_file);
        
        char query[512];
        snprintf(query, sizeof(query), 
                 "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s "
                 "AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
                 lat, lon, year, month, day, grib_file);
        
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            MYSQL_RES *result = mysql_store_result(conn);
            if (result) {
                MYSQL_ROW row = mysql_fetch_row(result);
                if (row && row[0]) {
                    char response[256];
                    snprintf(response, sizeof(response), 
                             "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: %s", row[0]);
                    send(client_socket, response, strlen(response), 0);
                } else {
                    const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNo data found";
                    send(client_socket, response, strlen(response), 0);
                }
                mysql_free_result(result);
            }
        }
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

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            mysql_close(conn);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket, conn);
    }

    mysql_close(conn);
    return 0;
}
