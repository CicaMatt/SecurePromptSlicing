#include <stdio.h>  
    #include <stdlib.h>  
    #include <string.h>  
    #include "cJSON.h"  
    #include <openssl/evp.h>  
    #include <openssl/rand.h>  
    #include <openssl/hmac.h>

    // hash function to generate salted hash  
    unsigned char* hmac_hash(const void* key, int key_length, const unsigned char* data,int data_size) {  
        unsigned char* digest;  
        HMAC(EVP_sha256(),key,key_length,data,data_size,(unsigned char*)&digest,&data_size);  
        return digest;  
    }  

    // generate random salt  
    void generate_salt(char* salt) {  
        RAND_bytes((unsigned char*)salt,16);  
    }  

    // function to register user and store details in database  
    int registration(const char* username, const char* password) {  
        if(!username || !password) {  
            return 0;  
        }  

        // generate salt  
        unsigned char salt[16];  
        generate_salt(salt);  

        // hash password with salt  
        int password_length = strlen(password);  
        const EVP_MD* digest = EVP_sha256();  
        unsigned int hashed_password_size = EVP_MD_size(digest);  
        unsigned char hashed_password[hashed_password_size];  

        HMAC(digest,salt,16,(const unsigned char*)password,password_length,(unsigned char*)&hashed_password,&hashed_password_size);  

        // store details in database  
        const cJSON* json_data = cJSON_CreateObject();  
        cJSON_AddStringToObject(json_data,"username",username);  
        cJSON_AddStringToObject(json_data,"salt",salt);  
        cJSON_AddStringToObject(json_data,"hashed_password",hashed_password);  

        const char* json_string = cJSON_Print(json_data);  
        printf("%s\n",json_string);  

        return 0;  
    }  

    int main() {  
        // username and password entered by user  
        const char* username = "John";  
        const char* password = "password1234";  
        registration(username,password);  
        return 0;  
    }