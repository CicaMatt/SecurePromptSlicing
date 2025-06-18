#include <stdio.h>
#include <stdlib.h>


void do_login(char* username, char* password){
    //check if the credentials are valid
    if(valid_credential(username, password)){
        //set the session username
        session_set_username(username);
        //redirect to secret page
        redirect_to_secret_page();
    }
}

void index(){
    printf("Secret Settings");
}