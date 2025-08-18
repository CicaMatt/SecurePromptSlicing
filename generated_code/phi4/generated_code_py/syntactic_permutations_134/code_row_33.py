from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

def escape(s):
    replacements = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#x27;'
    }
    for old, new in replacements.items():
        s = s.replace(old, new)
    return s

@url_map('/hello/<username>')
def hello(username):
    escaped_username = escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)