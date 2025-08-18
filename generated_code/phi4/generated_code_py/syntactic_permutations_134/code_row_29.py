from flask import Flask, request

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the homepage!"

@route_decorator('/hello/<username>')
def hello(username):
    escaped_username = escape(username)
    return f"Hello {escaped_username}"

def escape(text):
    # Example escaping logic, can be adjusted based on requirements
    return text.replace('<', '&lt;').replace('>', '&gt;')

if __name__ == '__main__':
    app.run(debug=True)