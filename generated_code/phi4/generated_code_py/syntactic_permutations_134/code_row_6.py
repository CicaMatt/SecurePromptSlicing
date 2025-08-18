from flask import Flask, request

app = Flask(__name__)

def url_to_function(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

def escape(text):
    replacements = {
        "&": "&amp;",
        "<": "&lt;",
        ">": "&gt;",
        '"': "&quot;",
        "'": "&#x27;"
    }
    for key, value in replacements.items():
        text = text.replace(key, value)
    return text

@url_to_function('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)