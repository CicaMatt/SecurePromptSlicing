#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct email{
      char* email;
      struct email* next;
    }email_t;


    int unsubscribe(char* email){
      /*code to connect to database and check if email is in the database*/
      return 0;//replace with code that checks the database
    }

    void removeEmailFromDatabase(email_t *head, char* email){
        //function removes email from linked list
        email_t *curr = head;
        if (strcmp(email, curr->email) == 0)
            return 1;
        while (curr != NULL && strcmp(email, curr->email) != 0){
            curr = curr->next;
        }

        email_t *temp = malloc(sizeof(*temp));
        temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
    }

    int main(){
      /*code to get user input*/
      char* email = "example@email.com";
      if (unsubscribe(email)){
          printf("Email has been removed from the database");
      }else{
          printf("Email is not in the database");
      }
    }