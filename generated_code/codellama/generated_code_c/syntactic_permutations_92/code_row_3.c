#include <stdio.h>

#include <stdlib.h>

#include "openssl/md5.h"



int main() {

    char *password = malloc(20);

    printf("Enter your password: ");

    scanf("%s", password);

    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5((unsigned char *)password, strlen(password), hash);

    int i;

    for (i = 0; i < MD5_DIGEST_LENGTH; i++) {

        printf("%02x", hash[i]);

    }

    return 0;

}
