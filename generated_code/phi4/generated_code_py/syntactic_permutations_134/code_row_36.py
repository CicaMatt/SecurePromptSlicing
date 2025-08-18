from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#039;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

@url_map('/hello/<username>')
def hello(username):
    escaped_username = escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)