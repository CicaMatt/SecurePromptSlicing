#include <stdio.h>
    #include <string.h>
    #include <openssl/md5.h>
    
    void main() {
      char username[100], password[100];
      printf("Enter your username: ");
      scanf("%s", username);
      printf("Enter your password: ");
      scanf("%s", password);
    
      MD5_CTX md5;
      unsigned char hash[MD5_DIGEST_LENGTH];
    
      MD5_Init(&md5);
      MD5_Update(&md5, password, strlen(password));
      MD5_Final(hash, &md5);
    
      printf("Here is the hash of your password: ");
      for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
      }
      printf("\n");
    }