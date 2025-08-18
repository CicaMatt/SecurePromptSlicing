#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket);
void process_query(MYSQL *conn, const char *lat, const char *lon, int year, int month, int day, const char *grib_file);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    while(1) {
        printf("Waiting for connections...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);

        close(new_socket);
    }

    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE - 1);
    
    if (valread > 0) {
        char *lat = strtok(buffer, ";");
        char *lon = strtok(NULL, ";");
        int year = atoi(strtok(NULL, ";"));
        int month = atoi(strtok(NULL, ";"));
        int day = atoi(strtok(NULL, ";"));
        char *grib_file = strtok(NULL, ";");

        if (lat && lon && grib_file) {
            MYSQL *conn;
            conn = mysql_init(NULL);

            if (!mysql_real_connect(conn, "localhost", "root", "password", "weather_db", 3306, NULL, 0)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return;
            }

            process_query(conn, lat, lon, year, month, day, grib_file);

            mysql_close(conn);
        }
    }
}

void process_query(MYSQL *conn, const char *lat, const char *lon, int year, int month, int day, const char *grib_file) {
    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", 
             lat, lon, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        char response[512];
        snprintf(response, sizeof(response), "Max Temperature: %s", row[0]);
        
        int client_socket = fileno(stdout);  // Assuming you want to print the result
        write(client_socket, response, strlen(response));
    }

    mysql_free_result(result);
}


Note: For this code to work, ensure that:
- The MySQL server is running with a database `weather_db` and table `temperature_data` having columns `latitude`, `longitude`, `year`, `month`, `day`, `grib_file`, and `temperature`.
- Replace `"root"` and `"password"` with the actual username and password for your MySQL setup.
- Compile this code using a C compiler linking against the MySQL client library, e.g., `gcc -o app app.c $(mysql_config --cflags --libs)`.