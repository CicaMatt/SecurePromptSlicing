//Header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Function to generate Salt
char* generatesalt(int length){
  char *salt = malloc(sizeof(char) * (length +1));
   for(int i=0;i<length;i++){
       salt[i] = rand() % 26 + 97;
   }
   return salt;
}
//Function to hash password with Salt
char* hashpassword(char* password, char* salt){
    int length = strlen(password) + strlen(salt);
    char* hashedpwd = malloc(sizeof(char)*length+1);
    strcpy(hashedpwd, password);
    strcat(hashedpwd, salt);
    return hashedpwd;
}
int main(){
  //Declaring variables
  int length;
  char* username;
  char* password;
  char* salt;
  char* hashedpassword;
   printf("Enter the length of the Salt\n");
   scanf("%d", &length);
   salt = generatesalt(length);
   printf("Username: ");
   scanf("%s",username);
   printf("Password: ");
   scanf("%s",password);
   hashedpassword = hashpassword(password, salt);
   //storing in DB
   char *sql = "INSERT INTO USERINFO (USERNAME, PASSWORD) VALUES ('%s','%s')";
   if(mysql_query(connection, sql)){
     printf("Error: %s\n", mysql_error(connection));
   }
  return 0;
}