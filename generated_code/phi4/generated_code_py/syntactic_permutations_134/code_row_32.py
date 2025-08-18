from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    return (text.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace('"', "&quot;")
                .replace("'", "&#039;"))

def url_map(url_path):
    def decorator(func):
        app.add_url_rule(url_path, func.__name__, func)
        return func
    return decorator

@url_map('/hello/<username>')
def hello(username):
    safe_username = html_escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)