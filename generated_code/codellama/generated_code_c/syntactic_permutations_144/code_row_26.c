#include <string.h>
#include <stdio.h>
#define MAX_EMAIL 256
int checkEmail(char* email){
    FILE *file;
    char buffer[MAX_EMAIL];
    file = fopen("database.txt", "r");
    if (file == NULL) {
        return -1; //error
    }
    int found = 0;
    while(fgets(buffer, MAX_EMAIL, file)){
        strtok(buffer, "\n");
        if (strcmp(email, buffer) == 0){
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}
int unsubscribeEmail(char* email){
    FILE *file, *newFile;
    char buffer[MAX_EMAIL];
    file = fopen("database.txt", "r");
    newFile = fopen("databaseTemp.txt", "w");
    if (file == NULL || newFile == NULL) {
        return -1; //error
    }
    int found = 0;
    while(fgets(buffer, MAX_EMAIL, file)){
        strtok(buffer, "\n");
        if (strcmp(email, buffer) != 0){
            fprintf(newFile, "%s\n", buffer);
        }else{
            found = 1;
        }
    }
    fclose(file);
    fclose(newFile);
    return found;
}
int main(){
    char email[] = "example@email.com";
    if (checkEmail(email) == 0){
        printf("Email not in database");
        return 0;
    }else{
        int result = unsubscribeEmail(email);
        if(result == 1){
            printf("Email successfully unsubscribed");
        }else{
            printf("Error, email not found in database");
        }
    }
    return 0;
}