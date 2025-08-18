from flask import Flask, request

app = Flask(__name__)

def url_mapper(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#x27;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

@url_mapper('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)