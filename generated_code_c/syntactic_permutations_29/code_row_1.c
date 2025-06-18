#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(void) {
    char target[1024];
    printf("Enter the url to redirect : ");
    fgets(target, sizeof(target), stdin);

    // check if the input string contains example.com
    regex_t reg;
    int reti;
    char msgbuf[100];
    reti = regcomp(&reg, "[^@]*@[^@]*", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&reg, target, 0, NULL, 0);
    if (!reti) {
        // Successful match
        printf("Match\n");
        //redirect to the input url
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        // No match
        printf("No match\n");
        //redirect to /
        redirect("/");
    } else {
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }
    regfree(&reg);
}