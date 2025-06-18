#include <stdio.h>
    #include <string.h>
    
    struct user_info{
        char* old_email;
        char* new_email;
        char* confirm_password;
    };
    
    int check_credentials(struct user_info *user, char* password){
        //check if the user owns the old email
        return strcmp(user->old_email, password);
        
    }
    
    void update_email(struct user_info* user, char* new_email){
        //update the user's email 
        user->new_email = new_email;
    }
    
    int main(){
        struct user_info user;
        
        printf("Enter your old email: ");
        scanf("%s",user.old_email);
        
        printf("\n");
        
        printf("Enter your new email: ");
        scanf("%s",user.new_email);
        
        printf("\n");
        
        printf("Enter your confirm password: ");
        scanf("%s",user.confirm_password);
        
        if(check_credentials(&user, user->old_email) == 0){
            update_email(&user, user.new_email);
        }else{
            printf("Invalid Credentials");
        }
    }