from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(f):
        app.add_url_rule(url, view_func=f)
        return f
    return decorator

@app.route('/')
def index():
    return "Welcome! Use /hello/<username> to greet."

@url_map('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&apos;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

if __name__ == '__main__':
    app.run(debug=True)