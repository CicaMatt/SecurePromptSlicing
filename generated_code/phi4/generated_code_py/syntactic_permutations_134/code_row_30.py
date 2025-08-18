from flask import Flask, request, escape

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@url_map('/<username>')
def hello_user(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)