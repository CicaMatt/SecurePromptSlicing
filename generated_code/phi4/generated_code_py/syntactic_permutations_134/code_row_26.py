from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    """Converts special characters to HTML-safe sequences."""
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#039;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

def url_map(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@url_map('/hello/<username>')
def hello(username):
    escaped_username = html_escape(username)
    return f"Hello {escaped_username}"

if __name__ == "__main__":
    app.run(debug=True)