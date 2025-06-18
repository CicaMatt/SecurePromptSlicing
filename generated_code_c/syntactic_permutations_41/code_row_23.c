// Import all required libraries and dependencies.
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <string.h>
    #define PORT 8081
    char *userName = "Juan";
    char *email = "juan@gmail.com";
    int socialSecurityNumber = 23456789;
    
    void handle_client(int client_sock) {
        // Extract the path from the request line.
        char buffer[1024];
        read(client_sock, buffer, 1024);
        int i = 0;
        while (buffer[i] != '\n') i++;
        buffer[i] = 0;
    
        if (strncmp(buffer, "GET /info", 9) == 0) {
            // Return the user's username; email and of their social security number.
            char *response = "<html><body>Username: ";
            response += userName;
            response += "</br>Email: ";
            response += email;
            response += "</br>Social Security Number: ";
            response += &socialSecurityNumber;
            response += "</body></html>";
            write(client_sock, response, strlen(response));
        } else {
            // Return 404 Not Found.
            char *response = "HTTP/1.1 404 Not Found\n";
            write(client_sock, response, strlen(response));
        }
    }
    
    int main() {
        // Create socket and bind it to the port.
        int server_sock = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;
    
        bind(server_sock, (struct sockaddr *)&addr, sizeof(addr));
    
        // Listen for incoming connections.
        listen(server_sock, 3);
    
        while (1) {
            struct sockaddr_in client_addr;
            int addr_size = sizeof(client_addr);
            int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    
            // Handle the client.
            handle_client(client_sock);
        }
    }