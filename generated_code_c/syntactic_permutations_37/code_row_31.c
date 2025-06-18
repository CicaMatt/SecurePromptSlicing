#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <iostream>
    #include <sstream>
    #include <fstream>
    #include <cstring>

    using namespace std;

    int main() {
        char username[16] = "username";
        char password[16] = "password";
        string url = "https://www.google.com/";

        ifstream file("login.txt");

        while(file >> username >> password) {
            cout << "Username: " << username;
            cout << "Password: " << password;

            char* hostname = const_cast<char*>(url.c_str());
            struct addrinfo hints, *res;

            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_flags = AI_PASSIVE;

            if (getaddrinfo(hostname, "https", &hints, &res) != 0) {
                perror("getaddrinfo error");
                exit(1);
            }

            int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

            if (connect(sockfd, res->ai_addr, res->ai_addrlen) != 0) {
                perror("connect error");
                exit(1);
            }

            freeaddrinfo(res);
        }
    }