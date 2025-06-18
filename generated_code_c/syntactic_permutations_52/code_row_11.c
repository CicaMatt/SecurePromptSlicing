#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "login.h"

// do_login function checks the user credentials and if they are correct it sets the username in the session and redirects to the secret page.

int do_login(char *username, char *password) {
   int uid = 0;
   char pw[256];
   struct passwd *p;
   if (!(p=getpwnam(username))){
       return -1;
    }
    strcpy(pw,crypt(password,p->pw_salt));
    if (strcmp(pw,p->pw_passwd)){
        return -2;
    }
    uid = p->pw_uid;
    setenv("USERNAME",username,1);
    printf("Hello %s! Welcome to the secret page.\n",username);
    return 0;
}

// main function checks for the username and password from the login page and calls do_login function.
int main(int argc, char *argv[]) {
   int i;
   if (argc < 3) {
       printf("Usage: %s username password\n",argv[0]);
       exit(1);
    }
    i = do_login(argv[1],argv[2]);
    switch (i) {
      case -1:
        printf("Invalid user!\n");
        break;
      case -2:
        printf("Wrong password!\n");
        break;
      default:
        exit(0);
     }
}