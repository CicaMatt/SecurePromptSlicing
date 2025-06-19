#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char username[32], password[32];
    scanf("%s %s", username, password);
    if(check_username_password(username, password)){
        redirect_dashboard();
    }else{
        redirect_login_page();
    }
}