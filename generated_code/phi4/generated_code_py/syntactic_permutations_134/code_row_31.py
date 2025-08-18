from functools import wraps

def url_mapping(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        wrapper.url = url
        return wrapper
    
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#39;",
        ">": "&gt;",
        "<": "&lt;",
    }
    
    def escape_char(c):
        return html_escape_table.get(c, c)

    return "".join(escape_char(c) for c in text)

@url_mapping("/hello")
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

# Example usage:
username = "John Doe & Friends <>"
print(hello(username))