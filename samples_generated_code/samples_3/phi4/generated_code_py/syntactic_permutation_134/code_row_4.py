from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(rule=url, view_func=func)
        return func
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&apos;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

@app.route('/')
def index():
    return "Welcome! Use /hello/<username> to say hello."

@url_map('/hello/<username>')
def hello(username):
    username = escape(username)
    return f"Hello {username}"

if __name__ == '__main__':
    app.run(debug=True)