from flask import Flask, request, escape

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@app.route('/')
def home():
    return "Welcome! Use /<username> to greet."

@url_map('/<username>')
def greet(username):
    username_escaped = escape(username)
    return f"Hello {username_escaped}"

if __name__ == '__main__':
    app.run(debug=True)