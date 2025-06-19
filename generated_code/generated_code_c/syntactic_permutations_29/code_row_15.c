#include<stdio.h>
    #include<string.h>
    #include<regex.h>
    #include<stdbool.h>
    
    int main(){
        char target[50];
        char regex[] = "example.com";
        regex_t reg;
        int reti;
        
        //Compile regular expression
        if(regcomp(&reg, regex, REG_EXTENDED) != 0){
            printf("Regex compilation failed\n");
            return 1;
        }
        
        //Take input for target URL
        scanf("%s", target);
        
        //Execute regular expression and check if it matches
        reti = regexec(&reg,target,0,NULL,0);
        if(!reti){
            printf("Target matched\n");
            //Redirect to the target URL
        }else{
            //If the regex doesn't match redirect to /
            printf("Target did not match\n");
        }
    return 0;
}