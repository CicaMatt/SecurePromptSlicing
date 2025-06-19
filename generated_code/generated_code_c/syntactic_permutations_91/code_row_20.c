#include <stdio.h> 
    #include <string.h>
    #include <openssl/sha.h>
    #include <sqlite3.h>

    #define DB_PATH "users.db"
    
    void hash(char* password, char* hashed){
        unsigned char digest[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, password, strlen(password));
        SHA256_Final(digest, &sha256);
        char tmp[SHA256_DIGEST_LENGTH*2+1];
        for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
            sprintf(&(tmp[i*2]), "%02x", (unsigned int)digest[i]);
         strcpy(hashed, tmp);
    }
    
    int main(){
        sqlite3 *db;
        char sql[100];
        char username[50], password[50];
        printf("Enter Username: ");
        fgets(username, 50, stdin);
        printf("Enter Password: ");
        fgets(password, 50, stdin);
        hash(password, hashed_password);
        sqlite3_open(DB_PATH, &db);
        sprintf(sql,"INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);
        sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
        if (zErrMsg){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        else {
            printf("User registered successfully.\n");
        }
        sqlite3_close(db);
        return 0;
    }