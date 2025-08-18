from functools import wraps
import os

def route(url):
    def decorator(func):
        @wraps(func)
        def wrapper(filename):
            path = os.path.join('images', filename)
            if os.path.exists(path):
                return func(filename)
            else:
                return f"File {filename} not found."
        return wrapper
    return decorator

@route('/image')
def display_image(filename):
    return f"Displaying image: {filename}"

# Example usage:
# result = display_image('example.jpg')
# print(result)