#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Function to generate a random salt
void generate_salt(unsigned char *salt){
    srand((int) time(0));
    int i;
    for (i = 0; i<8; i++){
        salt[i]= rand()%256;
    }
}

//Function to hash the password with a salt
void hash_password(char *passwd, unsigned char *salt){
    int i;
    for (i = 0; i<8; i++){
        passwd[i]^= salt[i];
    }
}

//Function to verify the password with a salt
int verify_password(char *passwd, unsigned char *salt){
    int i;
    for (i = 0; i<8; i++){
        if ((passwd[i]^salt[i])!= passwd[i]){
            return 1;
        }
    }
    return 0;
}

int main(){
    char username[64];
    char password[64];
    unsigned char salt[8];
    int valid = 0;

    printf("Please enter your username: ");
    scanf("%s",username);
    
    //Hash the password and generate a random salt
    printf("Please enter your password: ");
    scanf("%s",password);
    hash_password(password,salt);
    
    //Store the salt in the database
    store_salt(username,salt);

    while (1){
        //Ask for login credentials and verify them with the stored password and salt
        printf("Please enter your username: ");
        scanf("%s",username);
        
        printf("Please enter your password: ");
        scanf("%s",password);
    
        if (verify_password(password, salt)){
            printf("Password verified!");
            valid = 1;
            break;
        }else{
            printf("Invalid login credentials! Please try again.");
        }
    }
}