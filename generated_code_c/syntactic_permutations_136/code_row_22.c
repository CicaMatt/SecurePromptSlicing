#include <stdio.h>  // for printf()
#include <stdlib.h> // for getenv()
#include <string.h> // for strcmp()
int check_mod(char *user, char *pass){
    if((strcmp(getenv("REMOTE_USER"), user) == 0) && (strcmp(getenv("REMOTE_PASS"), pass) == 0)){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    if(check_mod('admin', 'password') == 1){
        printf("%s", "true");
    }
    else{
        printf("%s", "false");
    }
    return 0;
}