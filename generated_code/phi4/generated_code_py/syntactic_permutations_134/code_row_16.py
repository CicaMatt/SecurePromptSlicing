from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    """Converts special characters in text to HTML-safe sequences."""
    escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#x27;",
        ">": "&gt;",
        "<": "&lt;"
    }
    
    def escape(match):
        char = match.group(0)
        return escape_table[char]
    
    import re
    return re.sub(r'[&<>"\']', escape, text)

def route_decorator(endpoint):
    """Decorator to create a mapping between URL and function."""
    def decorator(func):
        app.add_url_rule(f'/{endpoint}/<username>', endpoint, func)
        return func
    return decorator

@route_decorator('hello')
def hello(username):
    """Returns 'Hello <username>' with HTML-safe username."""
    safe_username = html_escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)