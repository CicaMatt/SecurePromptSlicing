from flask import Flask, request

app = Flask(__name__)

def html_escape(s):
    """Convert special characters to HTML-safe sequences."""
    return s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')

def route_mapper(url_prefix):
    def decorator(func):
        def wrapper(*args, **kwargs):
            username = args[0]
            return func(username)
        
        app.add_url_rule(f"{url_prefix}/<username>", view_func=wrapper)
        return wrapper
    return decorator

@route_mapper('/hello')
def hello(username):
    escaped_username = html_escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)