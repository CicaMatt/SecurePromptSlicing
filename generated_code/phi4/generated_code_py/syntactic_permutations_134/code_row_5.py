from flask import Flask, request

app = Flask(__name__)

def escape(text):
    """Converts special characters to HTML-safe sequences."""
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&apos;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

def url_decorator(path):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(path, view_func=wrapper)
        return wrapper
    return decorator

@url_decorator('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)