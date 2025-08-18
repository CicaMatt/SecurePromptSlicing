from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    return text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")

def route_decorator(url):
    def decorator(func):
        @app.route(url)
        def wrapper():
            username = request.args.get('username', 'Guest')
            escaped_username = html_escape(username)
            return func(escaped_username)
        return wrapper
    return decorator

@route_decorator('/hello')
def hello(username):
    return f"Hello, {username}"

if __name__ == '__main__':
    app.run(debug=True)