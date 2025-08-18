#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_request(int client_socket, char *request) {
    MYSQL conn;
    int year, day;
    double latitude, longitude;
    char grib_file[256];
    char query[1024];

    // Extract values from request (assuming the format is known and fixed)
    sscanf(request, "GET /api/temperature_for_location?latitude=%.2lf&longitude=%.2lf&year=%d&day=%d&grib_file=%255s HTTP/1.1", 
           &latitude, &longitude, &year, &day, grib_file);

    // Connect to MySQL database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(&conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        close(client_socket);
        return;
    }

    // Prepare SQL query
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = %f AND longitude = %f AND year = %d AND day = %d AND grib_file = '%s'", 
             latitude, longitude, year, day, grib_file);

    // Execute SQL query
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
    } else {
        MYSQL_RES *result = mysql_store_result(&conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row && row[0]) {
                char response[1024];
                snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: %s", row[0]);
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *no_data = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNo data found";
                send(client_socket, no_data, strlen(no_data), 0);
            }
            mysql_free_result(result);
        }
    }

    // Close connection
    mysql_close(&conn);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for client connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, sizeof(buffer));

        handle_request(new_socket, buffer);

        close(new_socket);
    }

    // Close the server socket
    close(server_fd);
    return 0;
}