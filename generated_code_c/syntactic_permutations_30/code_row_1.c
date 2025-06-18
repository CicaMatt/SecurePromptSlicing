// Importing Libraries
 #include <stdio.h>
  #include <stdlib.h>
   #include <string.h>
    #include <regex.h>

//Defining a function for Redirect
void redirect(char *target) {
  char *command = malloc(strlen(target) + 12);
  strcpy(command, "xdg-open ");
  strcat(command, target);
  system(command);
}

//Main function to get the query parameter and redirect the user
int main() {
  char *target = getenv("QUERY_STRING");
  if (!target) {
    return 1;
  }

//Regular Expression for the target variable
 regex_t re;
   int status = regcomp(&re, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (status != 0) {
      return 1;
    }

//checking if the target variable matches the regular expression or not
   status = regexec(&re, target, 0, NULL, 0);
     regfree(&re);
       if (status == REG_NOMATCH) {
         redirect("/");
           return 0;
         } else {
          redirect(target);
            return 0;
        }
      }