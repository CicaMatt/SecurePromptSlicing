#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_request(int client_sock) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        // Extract parameters from request
        char *latitude_start = strstr(buffer, "latitude=");
        char *longitude_start = strstr(buffer, "longitude=");
        char *year_start = strstr(buffer, "year=");
        char *month_start = strstr(buffer, "month=");
        char *day_start = strstr(buffer, "day=");
        char *grib_file_start = strstr(buffer, "grib_file=");

        if (latitude_start && longitude_start && year_start && month_start && day_start && grib_file_start) {
            latitude_start += 9;
            longitude_start += 10;
            year_start += 5;
            month_start += 6;
            day_start += 4;
            grib_file_start += 10;

            char *latitude_end = strchr(latitude_start, '&');
            char *longitude_end = strchr(longitude_start, '&');
            char *year_end = strchr(year_start, '&');
            char *month_end = strchr(month_start, '&');
            char *day_end = strchr(day_start, '&');
            char *grib_file_end = buffer + bytes_received;

            if (!latitude_end) latitude_end = grib_file_start;
            if (!longitude_end) longitude_end = grib_file_start;
            if (!year_end) year_end = grib_file_start;
            if (!month_end) month_end = grib_file_start;
            if (!day_end) day_end = grib_file_start;

            char latitude[20], longitude[20], year[5], month[3], day[3], grib_file[100];

            strncpy(latitude, latitude_start, latitude_end - latitude_start);
            strncpy(longitude, longitude_start, longitude_end - longitude_start);
            strncpy(year, year_start, year_end - year_start);
            strncpy(month, month_start, month_end - month_start);
            strncpy(day, day_start, day_end - day_start);
            strncpy(grib_file, grib_file_start, grib_file_end - grib_file_start);

            latitude[latitude_end - latitude_start] = '\0';
            longitude[longitude_end - longitude_start] = '\0';
            year[year_end - year_start] = '\0';
            month[month_end - month_start] = '\0';
            day[day_end - day_start] = '\0';
            grib_file[grib_file_end - grib_file_start] = '\0';

            // Connect to MySQL database
            MYSQL *conn;
            conn = mysql_init(NULL);

            if (!mysql_real_connect(conn, "localhost", "root", "password", "weather_db", 3306, NULL, 0)) {
                char *error_msg = mysql_error(conn);
                printf("Connection error: %s\n", error_msg);
            } else {
                // Prepare SQL query
                char query[512];
                snprintf(query, sizeof(query), 
                         "SELECT MAX(temperature) FROM temperatures WHERE latitude='%s' AND longitude='%s' "
                         "AND year=%s AND month=%s AND day=%s AND grib_file='%s'", 
                         latitude, longitude, year, month, day, grib_file);

                if (mysql_query(conn, query)) {
                    char *error_msg = mysql_error(conn);
                    printf("Query error: %s\n", error_msg);
                } else {
                    MYSQL_RES *result = mysql_store_result(conn);
                    MYSQL_ROW row = mysql_fetch_row(result);
                    if (row) {
                        printf("Max Temperature: %s\n", row[0]);
                    }
                    mysql_free_result(result);
                }

                mysql_close(conn);
            }
        }
    }

    close(client_sock);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
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
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);
    }

    return 0;
}