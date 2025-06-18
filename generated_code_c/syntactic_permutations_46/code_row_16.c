#include <stdio.h>

//Decorator for img() function
@app.route("/img")
def img():
    #Function opens "images/name" file and returns the file object
    return open("images/name", "r")