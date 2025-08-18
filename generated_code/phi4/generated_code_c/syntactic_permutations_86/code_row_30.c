#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_connection(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';

        // Parse the request to extract query parameters
        char *latitude_str = strstr(buffer, "latitude=");
        char *longitude_str = strstr(buffer, "longitude=");
        char *year_str = strstr(buffer, "year=");
        char *month_str = strstr(buffer, "month=");
        char *day_str = strstr(buffer, "day=");
        char *grib_file_str = strstr(buffer, "grib_file=");

        if (latitude_str && longitude_str && year_str && month_str && day_str && grib_file_str) {
            latitude_str += 9;
            longitude_str += 10;
            year_str += 5;
            month_str += 6;
            day_str += 4;
            grib_file_str += 10;

            char *latitude_end = strchr(latitude_str, '&');
            char *longitude_end = strchr(longitude_str, '&');
            char *year_end = strchr(year_str, '&');
            char *month_end = strchr(month_str, '&');
            char *day_end = strchr(day_str, '&');
            char *grib_file_end = strchr(grib_file_str, ' ');

            if (latitude_end) *latitude_end = '\0';
            if (longitude_end) *longitude_end = '\0';
            if (year_end) *year_end = '\0';
            if (month_end) *month_end = '\0';
            if (day_end) *day_end = '\0';
            if (grib_file_end) *grib_file_end = '\0';

            // Connect to MySQL database
            MYSQL *conn;
            conn = mysql_init(NULL);

            if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
                printf("Database connection failed: %s\n", mysql_error(conn));
                return;
            }

            // Prepare the SQL query
            char query[BUFFER_SIZE];
            snprintf(query, sizeof(query),
                     "SELECT MAX(temperature) FROM temperatures WHERE latitude = '%s' AND longitude = '%s' "
                     "AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
                     latitude_str, longitude_str, year_str, month_str, day_str, grib_file_str);

            // Execute the query
            if (mysql_query(conn, query)) {
                printf("Query execution failed: %s\n", mysql_error(conn));
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                if (result) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    char response[BUFFER_SIZE];
                    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: %s\n", row[0]);
                    send(client_socket, response, strlen(response), 0);
                }
                mysql_free_result(result);
            }

            mysql_close(conn);
        } else {
            char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request format.\n";
            send(client_socket, response, strlen(response), 0);
        }
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

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
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

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_connection(new_socket);
    }

    return 0;
}