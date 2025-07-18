#include <stdio.h>
#include <string.h>
#include "urllib2"
 
void decorator(str url, str func):
    # map each URL given as an argument to the function that follows it.
    pass
 
def hello(username):
    return "Hello %s"%(escape(username))
 
@decorator("/hello/<username>")
def hello(username):
    # return a string with the text 'Hello' concatenated
    # to the value of username.
    pass