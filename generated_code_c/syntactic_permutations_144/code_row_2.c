#include <stdio.h>
int check_email(char* email){
    int exists;
    //check if email exists in db
    exists = 0;//assume email doesn't exist
    return exists;
}
int unsubscribe(char *email){
    int retval=0;
    //call script that unsubscribes the email
    //if successful set retval to 1
    return retval;
}
int main(){
   char email[] = "someone@example.com";
   if(check_email(email) == 0){
       printf("email doesn't exist\n");
   }else{
       unsubscribe(email);
   }
}