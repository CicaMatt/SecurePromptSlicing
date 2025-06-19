#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to generate random numbers
int generate_random_number(int num) {
    int x;
    x = (rand() % 9000);
    return x + 1000;
}

// Function to get info from user
void info() {
    char username[256];
    char email[256];
    int ssn;
    printf("Username: ");
    scanf("%s", username);
    printf("Email: ");
    scanf("%s", email);
    ssn = generate_random_number(1000);
    
    // Print info from user
    printf("User Info:\n");
    printf("Username: %s\nEmail: %s\nSSN: %d\n", username, email, ssn);
}

// Main function
int main() {
    info();
    return 0;
}