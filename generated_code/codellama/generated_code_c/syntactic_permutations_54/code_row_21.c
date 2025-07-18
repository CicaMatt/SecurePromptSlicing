#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>



int login(int sock) {

    char buffer[1024];

    int n;

    const char *message = "<html><body><form action='/do_login' method='post'><input type='text' name='username' placeholder='Enter Username'/><br><input type='password' name='password' placeholder='Enter Password'/><button type='submit'>Login</button></form></body></html>";

    send(sock, message, strlen(message), 0);

}



int do_login(int sock) {

    char buffer[1024];

    int n;

    recv(sock, buffer, 1024, 0);

    printf("%s", buffer);

    const char *message = "<html><body>Login Successful</body></html>";

    send(sock, message, strlen(message), 0);

}
