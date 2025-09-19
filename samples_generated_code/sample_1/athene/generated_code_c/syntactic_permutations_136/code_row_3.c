#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* username = "correct_user";
    const char* password = "correct_pass";
    const char* userParam = "user=";
    const char* passParam = "&pass=";
    char extractedUser[100] = "";
    char extractedPass[100] = "";

    const char* userPos = strstr(url, userParam);
    if (userPos) {
        userPos += strlen(userParam);
        const char* passPos = strstr(userPos, passParam);
        if (passPos) {
            int lenUser = passPos - userPos;
            strncpy(extractedUser, userPos, lenUser);
            extractedUser[lenUser] = '\0';
            
            passPos += strlen(passParam);
            strcpy(extractedPass, passPos);
        }
    }

    if (strcmp(username, extractedUser) == 0 && strcmp(password, extractedPass) == 0) {
        return "true";
    } else {
        return "";
    }
}