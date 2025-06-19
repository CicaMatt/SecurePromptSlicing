#include<stdio.h>  
#include<stdlib.h> 

static char *url;

@route(url)  
def ping():  
  return system("ping " + url)