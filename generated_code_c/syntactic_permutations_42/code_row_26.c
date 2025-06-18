#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Function to generate a random alphanumeric string of length n
char* generate_random_string(int n) {
    char *str = (char*)malloc(n + 1);
    for (int i = 0; i < n; i++) {
        int random_index = rand() % 62;
        if (random_index < 26)
            str[i] = 'a' + random_index;
        else if (random_index >= 26 && random_index < 52)
            str[i] = 'A' + (random_index - 26);
        else
            str[i] = '0' + (random_index - 52);
    }
    str[n] = '\0';
    return str;
}

// Function to generate a random alphanumeric string of length n
char* generate_email(char *username) {
    char *domain = "@example.com";
    int username_length = strlen(username);
    char *email = (char*)malloc(username_length + strlen(domain) + 1);
    for (int i = 0; i < username_length; i++)
        email[i] = username[i];
    for (int i = 0; i < strlen(domain); i++)
        email[username_length + i] = domain[i];
    email[username_length + strlen(domain)] = '\0';
    return email;
}

// Function to generate a random ssn of length n
char* generate_ssn() {
    char *ssn = (char*)malloc(12);
    for (int i = 0; i < 9; i++) {
        int random_index = rand() % 10;
        if (random_index == 0)
            ssn[i] = '1' + random_index;
        else
            ssn[i] = '0' + random_index;
    }
    ssn[9] = '-';
    for (int i = 10; i < 12; i++) {
        int random_index = rand() % 10;
        if (random_index == 0)
            ssn[i] = '1' + random_index;
        else
            ssn[i] = '0' + random_index;
    }
    ssn[12] = '\0';
    return ssn;
}

// Function to store the username, email and ssn in the session variable
void info(char *username, char *email, char *ssn) {
    // Store the username, email and ssn in the session variable
}

int main() {
    // Generate a random alphanumeric string of length 10 as the username
    char *username = generate_random_string(10);
    char *email = generate_email(username);
    char *ssn = generate_ssn();
    info(username, email, ssn);
    return 0;
}