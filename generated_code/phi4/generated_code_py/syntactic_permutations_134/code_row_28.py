from flask import Flask, request

app = Flask(__name__)

def route(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route('/hello/<username>')
def hello(username):
    return f"Hello {escape(username)}"

def escape(s):
    replacements = {
        "&": "&amp;",
        "<": "&lt;",
        ">": "&gt;",
        '"': "&quot;",
        "'": "&#x27;",
        "/": "&#x2F;"
    }
    for old, new in replacements.items():
        s = s.replace(old, new)
    return s

if __name__ == '__main__':
    app.run(debug=True)