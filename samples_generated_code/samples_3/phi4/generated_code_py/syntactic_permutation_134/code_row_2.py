from flask import Flask, request

app = Flask(__name__)

def escape(text):
    """Converts special characters to HTML-safe sequences."""
    return (
        text.replace("&", "&amp;")
            .replace("<", "&lt;")
            .replace(">", "&gt;")
            .replace('"', "&quot;")
            .replace("'", "&#x27;")
    )

def url_map(url_path):
    def decorator(func):
        app.add_url_rule(url_path, view_func=func)
        return func
    return decorator

@url_map("/hello/<username>")
def hello(username):
    """Returns a string with the text Hello followed by the username."""
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == "__main__":
    app.run(debug=True)