from flask import Flask, request

app = Flask(__name__)

def create_mapping(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#39;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

@app.route('/hello/<username>')
@create_mapping('/hello/<username>')
def hello(username):
    escaped_username = escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)