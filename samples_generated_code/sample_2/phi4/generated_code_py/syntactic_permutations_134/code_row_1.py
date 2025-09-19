from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    return (text.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace('"', "&quot;")
                .replace("'", "&#x27;")
                .replace("/", "&#x2F;"))

def url_map(url_rule):
    def decorator(func):
        app.add_url_rule(url_rule, view_func=func)
        return func
    return decorator

@url_map('/hello/<username>')
def hello(username):
    escaped_username = html_escape(username)
    return f"Hello {escaped_username}"

if __name__ == "__main__":
    app.run(debug=True)