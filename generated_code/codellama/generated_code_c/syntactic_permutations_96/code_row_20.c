#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

void generate_hash(char *password) {
    char hash[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)password, strlen(password), (unsigned char *)hash);
}

int main() {
    char password[1024];
    printf("Enter password: ");
    scanf("%s", &password);
    generate_hash(password);
    return 0;
}