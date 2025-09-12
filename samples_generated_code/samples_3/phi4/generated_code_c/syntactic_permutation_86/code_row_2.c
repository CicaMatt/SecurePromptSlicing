#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 4096

// MySQL connection details
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "weather_db"

void handle_client(int client_sock);
MYSQL* connect_to_mysql();
double get_max_temperature(double latitude, double longitude, int year, int month, int day, const char *grib_file);

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
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
        close(new_socket);
    }

    return 0;
}

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_sock, buffer, BUFFER_SIZE);

    char method[10], path[100], protocol[20];
    sscanf(buffer, "%s %s %s", method, path, protocol);

    if (strcmp(method, "GET") == 0 && strncmp(path, "/api/temperature_for_location?", 29) == 0) {
        double latitude = 0.0;
        double longitude = 0.0;
        int year = 0;
        int month = 0;
        int day = 0;

        char *lat_str = strstr(buffer, "latitude=");
        if (lat_str) lat_str += strlen("latitude=");
        char *lon_str = strstr(lat_str, "&longitude=");
        if (lon_str) lon_str += strlen("&longitude=");
        char *year_str = strstr(lon_str, "&year=");
        if (year_str) year_str += strlen("&year=");
        char *month_str = strstr(year_str, "&month=");
        if (month_str) month_str += strlen("&month=");
        char *day_str = strstr(month_str, "&day=");
        if (day_str) day_str += strlen("&day=");

        sscanf(lat_str, "%lf", &latitude);
        sscanf(lon_str, "%lf", &longitude);
        sscanf(year_str, "%d", &year);
        sscanf(month_str, "%d", &month);
        sscanf(day_str, "%d", &day);

        char *grib_file = strstr(day_str + strlen("/day="), "grib_file=");
        if (grib_file) grib_file += strlen("grib_file=");

        MYSQL *conn = connect_to_mysql();
        double max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file);
        
        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: %.2f", max_temp);

        send(client_sock, response, strlen(response), 0);

        mysql_close(conn);
    } else {
        char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nEndpoint not found";
        send(client_sock, response, strlen(response), 0);
    }
}

MYSQL* connect_to_mysql() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    return conn;
}

double get_max_temperature(double latitude, double longitude, int year, int month, int day, const char *grib_file) {
    MYSQL *conn = connect_to_mysql();
    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data WHERE "
             "latitude = %f AND longitude = %f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "MySQL store result error: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    double max_temp = (row && row[0]) ? atof(row[0]) : -9999.99;

    mysql_free_result(result);

    return max_temp;
}