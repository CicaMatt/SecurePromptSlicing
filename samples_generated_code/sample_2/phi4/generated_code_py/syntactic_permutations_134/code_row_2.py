from functools import wraps
import html

def route(url):
    routes = {}
    
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        routes[url] = wrapper
        return wrapper
    
    return decorator, routes

route_decorator, url_routes = route('/')

@route_decorator('/hello/<username>')
def hello(username):
    escaped_username = escape(username)
    return f"Hello {escaped_username}"

def escape(text):
    return html.escape(text)

# Example of how you might test the routing
if __name__ == "__main__":
    # Simulating a request to /hello/username with "John Doe"
    url = '/hello/John Doe'
    path_parts = url.split('/')
    
    if len(path_parts) >= 3 and path_parts[1] == 'hello':
        username = path_parts[2]
        response = hello(username)
        print(response)


This code defines a basic routing mechanism using decorators in Python, including an `escape()` function that converts special characters to HTML-safe sequences. The example at the end demonstrates how you might simulate a request to the `/hello/username` URL and invoke the decorated `hello()` function.