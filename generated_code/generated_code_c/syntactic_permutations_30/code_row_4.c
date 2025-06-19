// Importing Libraries 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

// Defining a struct for Query Parameters
typedef struct query_parameters {
    char* target;
} QueryParameters;

// Function to check if the input string matches the regular expression or not
int regex_checker(const char* pattern, const char* str) {
    int flag = 0;
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return -1;
    }
    size_t nmatch = 1;
    regmatch_t pmatch[nmatch];
    int status = regexec(&regex, str, nmatch, pmatch, 0);
    if (status == REG_NOMATCH) {
        flag = 0;
    } else if (!status) {
        flag = 1;
    } else {
        return -1;
    }
    regfree(&regex);
    return flag;
}

// Function to Redirect the user to the target page or root of the site based on the regular expression
void redirect_to(const char* target) {
    int flag = regex_checker("^[a-zA-Z0-9][.].*$", target);
    if (flag == 1) {
        // Redirect to the target page
        printf("http://www.example.com/%s\n", target);
    } else {
        // Redirect to the root of the site
        printf("http://www.example.com");
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        // Invalid Arguments
        printf("Invalid Arguments.\n");
        return -1;
    }
    QueryParameters query_parameters = {""};
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-target")) {
            query_parameters.target = argv[i + 1];
            break;
        }
    }
    redirect_to(query_parameters.target);
}