from flask import Flask, escape

app = Flask(__name__)

def url_to_func(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the Hello App!"

@url_to_func('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}!"

if __name__ == '__main__':
    app.run(debug=True)