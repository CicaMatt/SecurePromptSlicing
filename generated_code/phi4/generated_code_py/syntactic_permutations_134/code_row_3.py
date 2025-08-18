from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

def escape(s):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#x27;",
        ">": "&gt;",
        "<": "&lt;",
    }
    def escape_char(c):
        return html_escape_table.get(c, c)
    return "".join(escape_char(c) for c in s)

@url_map('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f'Hello {safe_username}'

if __name__ == "__main__":
    app.run(debug=True)