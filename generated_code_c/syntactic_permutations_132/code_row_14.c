//header files
#include <stdio.h>
#include <stdlib.h>

//define function decorator
#define bind(x) x

//function to be called when user visits URL //<username>
bind("/<username>") void func()
{
    char username[20];
    gets(username);
    
    //render template and pass username variable value to template.html
    render("template.html", {"username":username}); 
}