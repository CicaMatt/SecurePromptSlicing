#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
#define MAXLEN 200

struct user_data {
    char username[MAXLEN];
    char hashed_password[32+1];
    char first_name[MAXLEN];
    char last_name[MAXLEN];
    char email[MAXLEN];
};

void check_username(char username[]) {
    struct user_data data = {};
    FILE *fp = fopen("user.csv", "r");
    while (fscanf(fp, "%[^;];%s;%[^;];%[^;];%[^\n]\n",
                  data.username,
                  data.hashed_password,
                  data.first_name,
                  data.last_name,
                  data.email) != EOF)
    {
        if (strcmp(data.username, username) == 0) {
            printf("Username already exists");
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

int main() {
    char *password = NULL;
    size_t len;
    struct user_data data;
    MD5_CTX md5_ctx;
    unsigned char md5_hash[MD5_DIGEST_LENGTH];

    printf("Enter your desired username: ");
    scanf("%s", data.username);
    check_username(data.username);
    
    printf("Enter your password: ");
    getline(&password, &len, stdin);
    strcpy(data.hashed_password, MD5(password, strlen(password), md5_hash));
    free(password);
    
    printf("Enter your first name: ");
    scanf("%s", data.first_name);
    
    printf("Enter your last name: ");
    scanf("%s", data.last_name);
    
    printf("Enter your email address: ");
    scanf("%s", data.email);

    FILE *fp = fopen("user.csv", "a");
    if (fp == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s;%s;%s;%s;%s\n",
            data.username,
            data.hashed_password,
            data.first_name,
            data.last_name,
            data.email);
    fclose(fp);

    printf("Registration successful");
    exit(EXIT_SUCCESS);
}