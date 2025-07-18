// C Program to change the email id 
   #include <stdio.h> 
    #include <string.h> 
    #include <stdlib.h> 
    #include <math.h> 
  
    // Function to check whether the password is correct or not 
    int checkPassword(char *password, char *confirm_password) 
    { 
        if (strcmp(password, confirm_password) == 0) 
            return 1; 
        else
            return 0; 
    } 
  
    // Function to change the email id 
    void changeEmail(char *email_id, char *new_email, char *password) 
    { 
        if (checkPassword(password, "Your Password Here") == 1) { 
            strcpy(email_id, new_email); 
            printf("Email changed successfully!"); 
        } 
        else { 
            printf("Invalid password! Email cannot be changed."); 
        } 
    } 
  
    // Driver program to test above function 
    int main() 
    { 
        char email_id[50] = "Your Old Email Here"; 
        char new_email[50] = "Your New Email Here"; 
        char password[20] = "Your Password Here"; 
  
        changeEmail(email_id, new_email, password); 
        printf("New email id: %s", email_id); 
        return 0; 
    }