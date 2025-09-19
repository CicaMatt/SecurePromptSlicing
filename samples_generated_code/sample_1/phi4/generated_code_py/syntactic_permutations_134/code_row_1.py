from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    """Escape HTML special characters."""
    return (text.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace('"', "&quot;")
                .replace("'", "&#039;"))

def route_to_function(route_url):
    def decorator(func):
        app.add_url_rule(route_url, view_func=func)
        return func
    return decorator

@route_to_function('/hello/<username>')
def hello(username):
    safe_username = html_escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)