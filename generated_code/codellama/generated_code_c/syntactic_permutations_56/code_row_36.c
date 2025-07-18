//header file login_page.h
typedef struct login_info {
    char* old_email;
    char* new_email;
    char* password;
} login_info_t;

int login(login_info_t* info);
int change_email(login_info_t* info);

//source file login_page.c
#include "login_page.h"
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 64

int login(login_info_t* info) {
    char buffer[BUFFER_SIZE];
    printf("Enter your email: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%s", info->old_email);
    printf("Enter your password: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%s", info->password);
    return 0;
}

int change_email(login_info_t* info) {
    char buffer[BUFFER_SIZE];
    printf("Enter your new email: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%s", info->new_email);
    printf("Confirm password: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (strcmp(info->password, buffer) != 0) {
        return -1;
    }
    if (strcmp(info->old_email, info->new_email) == 0) {
        return -2;
    }
    strcpy(info->old_email, info->new_email);
    memset(buffer, 0, sizeof(buffer));
    printf("Email changed successfully\n");
    return 0;
}