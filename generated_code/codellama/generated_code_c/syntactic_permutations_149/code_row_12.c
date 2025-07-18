#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netdb.h>

    void insert_user_message_in_db(const char *username, const char *message) {
        // Connect to database
        // Insert message into table with username
        // Disconnect from database
    }

    void display_messages() {
        // Connect to database
        // Get all messages from the table
        // Print each message on a new line in the format "Username: Message"
        // Disconnect from database
    }

    int main(int argc, char *argv[]) {
        int sock, n;
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo("localhost", "8080", &hints, &res) != 0) {
            perror("Unable to resolve host");
            exit(1);
        }

        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
            perror("Unable to connect");
            exit(1);
        }

        char *username = "User";
        char *message = "Hello from User!";
        insert_user_message_in_db(username, message);
        display_messages();

        close(sock);
        return 0;
    }