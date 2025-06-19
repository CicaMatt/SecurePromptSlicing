#include <stdio.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>
    #include <string.h>
    #include <stdint.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <signal.h>
    #include <unistd.h>
    
    void handler(int sig) {
        printf("Caught signal %d\n",sig);
        exit(1);
    }
    
    int main(int argc, char const *argv[]) {
        
        /* Server setup */
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(8080);
        server.sin_addr.s_addr = INADDR_ANY;
    
        /* Create the socket */
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        
        signal(SIGINT, handler);
        
        /* Bind the socket to the address and port */
        bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    
        /* Listen on the socket */
        listen(server_fd, 5);
    
        while(1) {
            
            char *latitude;
            char *longitude;
            char *year;
            char *month;
            char *day;
            char *grib_file;
            
            /* Accept a connection */
            int client = accept(server_fd, NULL, NULL);
    
            /* Receive the latitude and longitude from the client */
            recv(client, latitude, 1024, 0);
            recv(client, longitude, 1024, 0);
            
            /* Extract the year; month; day and grib_file from the request */
            char *query = "SELECT MAX(temperature) FROM weather WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s";
            
            /* Connect to MySQL and execute the query */
            MYSQL *mysql;
            mysql_init(&mysql);
            if (!mysql_real_connect(&mysql,"localhost","user","password","mydatabase",0,NULL,0)) {
                printf("Failed to connect\n");
                return 1;
            }
            
            /* Execute the query */
            MYSQL_RES *result = mysql_store_result(&mysql);
            
            /* Fetch the result */
            int num_fields = mysql_num_fields(result);
            while (MYSQL_ROW row = mysql_fetch_row(result)) {
                for(int i = 0; i < num_fields; i++) {
                    printf("%s ",row[i]);
                }
                printf("\n");
            }
            
            /* Close the connection */
            mysql_close(&mysql);
    
        }
        
        return 0;
    }