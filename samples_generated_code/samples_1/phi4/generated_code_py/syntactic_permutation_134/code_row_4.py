from functools import wraps
from html import escape

routes = {}

def route(url):
    def decorator(func):
        routes[url] = func
        
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        return wrapper
    return decorator

@route('/hello/<username>')
def hello(username):
    username_escaped = escape(username)
    return f"Hello, {username_escaped}!"

# Example usage:
if __name__ == '__main__':
    # Simulating a user navigating to /hello/john_doe
    url = '/hello/john_doe'
    
    if url in routes:
        response = routes[url](username='john_doe')
        print(response)
    else:
        print("404 Not Found")