from functools import wraps
import re

def url_to_function(url_pattern):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        # Mapping URLs to functions (simplified version for demonstration)
        if not hasattr(wrapper, 'url_map'):
            wrapper.url_map = {}
        match = re.match(url_pattern.replace("<variable>", "(?P<username>[^/]+)"), "/hello/<variable>")
        if match:
            username = match.group("username")
            wrapper.url_map[match.group(0)] = lambda: func(username)
        
        return wrapper
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&apos;",
        ">": "&gt;",
        "<": "&lt;",
    }
    def escape_char(match):
        return html_escape_table[match.group(0)]
    
    return re.sub(r'[&\"\'><]', escape_char, text)

@url_to_function("/hello/<variable>")
def hello(username):
    username = escape(username)
    return f"Hello {username}"

# Example of calling the function directly
print(hello("John Doe"))  # Direct call

# Simulating URL navigation
for url, func in hello.url_map.items():
    print(func())  # Output for /hello/John%20Doe would be "Hello John Doe"