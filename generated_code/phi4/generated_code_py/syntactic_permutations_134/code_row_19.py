from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

def escape(text):
    return (text.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace('"', "&quot;")
                .replace("'", "&#039;"))

@url_map('/hello/<username>')
def hello(username):
    username = escape(username)
    return f"Hello {username}"

if __name__ == '__main__':
    app.run(debug=True)