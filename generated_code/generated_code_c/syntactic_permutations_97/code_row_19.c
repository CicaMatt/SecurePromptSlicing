#include <stdio.h> 
#include <stdlib.h> 
#include<string.h> 

int main() { 
    char username[50]; 
    char password[50]; 
    char first_name[50]; 
    char last_name[50]; 
    char email[100]; 
    
    printf("Username: "); 
    scanf("%s", username); 
    printf("Password: "); 
    scanf("%s", password); 
    printf("First Name: "); 
    scanf("%s", first_name); 
    printf("Last Name: "); 
    scanf("%s", last_name); 
    printf("Email: "); 
    scanf("%s", email); 
    
    FILE *fp; 
    fp = fopen("user.txt", "r"); 
    
    if (fp == NULL) { 
        fprintf(stderr, "Error while opening the file.\n"); 
        exit(0); 
    } 
    
    char c[100]; 
    int count = 0; 
    
    while(!feof(fp)) { 
        fscanf(fp, "%s", c); 
        
        if (strcmp(c, username) == 0) { 
            printf("Username already exists.\n"); 
            count = 1; 
            break; 
        } 
    } 
    
    fclose(fp); 
    
    if (count == 0) { 
        FILE *ft; 
        ft = fopen("user.txt", "a"); 
        
        if (ft == NULL) { 
            fprintf(stderr, "Error while opening the file.\n"); 
            exit(0); 
        } 
        
        char hash_pass[100]; 
        for(int i = 0; password[i] != '\0'; i++) { 
            int x = (password[i] + 5) % 26 + 'a'; 
            hash_pass[i] = x; 
        } 
        
        fprintf(ft, "%s %s %s %s %s\n", username, hash_pass, first_name, last_name, email); 
        printf("Registration Successful.\n"); 
    } 
    
    return 0; 
}