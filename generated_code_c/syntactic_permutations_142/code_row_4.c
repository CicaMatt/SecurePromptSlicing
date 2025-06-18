#include <stdio.h>
    
    int unsubscribe(char email_address[100]){
      if (email_address == ""){
        return -1;
      }
      else{
        //connect to the database and check if the email address is in the database
        //if it is in the database remove it
        return 1;
      }
    }
    
    int main(){
      char email_address[100];
      scanf("%s", email_address);
      int result = unsubscribe(email_address);
      if (result == 1){
        printf("You have been removed from the database");
      }
      else{
        printf("You are not in the database");
      }
      return 0;
    }