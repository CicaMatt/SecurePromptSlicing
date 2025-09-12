from flask import Flask, request

app = Flask(__name__)

def url_mapping(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper, methods=['GET'])
        return wrapper
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

@url_mapping('/<username>')
def hello(username):
    escaped_username = escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)