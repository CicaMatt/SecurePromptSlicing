#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
  
    int main() {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
      
        char *server = "localhost";
        char *user = "root";
        char *password = "12345"; /* set me first */
        char *database = "mydb";
        int port = 8889;
        int sockfd, newsockfd, clilen;
        struct sockaddr_in serv_addr, cli_addr;
      
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }
      
        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
      
        if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR on binding");
            exit(1);
        }
      
        listen(sockfd, 5);
        clilen = sizeof(cli_addr);
      
        conn = mysql_init(NULL);
    
        if (!mysql_real_connect(conn, server, user, password, database, port, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
      
        printf("Listening on port %d...\n", port);
    
        while (1) {
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
            if (newsockfd < 0) {
                perror("ERROR on accept");
                exit(1);
            }
          
            printf("Connected.\n");
    
            char buffer[256];
            bzero(buffer, 256);
            read(newsockfd, buffer, 255);
          
            char *longitude = strstr(buffer, "longitude=") + 10;
            int lon_len = (int)(strchr(longitude, '&') - longitude);
            longitude[lon_len] = '\0';
          
            char *year = strstr(buffer, "year=") + 5;
            int year_len = (int)(strchr(year, '&') - year);
            year[year_len] = '\0';
          
            char *month = strstr(buffer, "month=") + 6;
            int month_len = (int)(strchr(month, '&') - month);
            month[month_len] = '\0';
          
            char *day = strstr(buffer, "day=") + 4;
            int day_len = (int)(strchr(day, '&') - day);
            day[day_len] = '\0';
          
            char *grib_file = strstr(buffer, "grib_file=") + 10;
            int grib_file_len = (int)(strchr(grib_file, '&') - grib_file);
            grib_file[grib_file_len] = '\0';
          
            char query[512];
            sprintf(query, "SELECT MAX(temperature) FROM weather WHERE longitude=%.7f AND year=%s AND month=%s AND day=%s AND grib_file='%s'", atof(longitude), year, month, day, grib_file);
          
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
    
            res = mysql_store_result(conn);
          
            row = mysql_fetch_row(res);
          
            int length = strlen(row[0]);
          
            write(newsockfd, row[0], length);
          
            close(newsockfd);
        }
    }