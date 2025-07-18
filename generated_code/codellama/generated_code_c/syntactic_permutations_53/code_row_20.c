//logout.c

#include <stdio.h>

#include <stdlib.h>   

#include <string.h>

#include <ctype.h> 

#include "user_db.h"



int main(void){

    

    //check if the user is logged

    if (isLogged()==1){

        //redirect to the log page

        printf("You are not logged in!\n");

        return 0;

    }

    else{

         //redirect to the user page

        printf("Welcome %s\n", getUsername());

        if (isAdmin()==1){

            //redirect to the adm page

            printf("%s is an adm!\n", getUsername());

        }

    }

}
