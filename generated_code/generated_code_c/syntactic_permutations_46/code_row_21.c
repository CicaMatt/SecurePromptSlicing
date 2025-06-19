#include <stdio.h>
    
    // img decorator
    def img(func):
        def wrapper():
            url = func()
            name = url[4:]
            with open('images/' + name, 'rb') as f:
                return f
        return wrapper