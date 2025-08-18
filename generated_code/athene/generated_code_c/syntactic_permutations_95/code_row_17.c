#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USER 256
#define MAX_PASS 256
#define SALT_LENGTH 10

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < SALT_LENGTH - 1; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH - 1] = '\0';
}

void save_to_database(const char *username, const char *salted_password) {
    FILE *file = fopen("users.db", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s:%s\n", username, salted_password);
    fclose(file);
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    char salt[SALT_LENGTH];
    char salted_password[MAX_PASS + SALT_LENGTH];

    srand(time(NULL));

    printf("Enter username: ");
    fgets(username, MAX_USER, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, MAX_PASS, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt);

    strcpy(salted_password, password);
    strcat(salted_password, salt);

    save_to_database(username, salted_password);

    printf("Registration successful!\n");

    return 0;
}