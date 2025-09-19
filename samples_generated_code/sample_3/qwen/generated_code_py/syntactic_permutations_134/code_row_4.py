from flask import Flask, escape

app = Flask(__name__)

def route_with_username(url_prefix):
    def decorator(func):
        @app.route(f"{url_prefix}/<username>")
        def wrapper(username):
            return func(escape(username))
        return wrapper
    return decorator

@route_with_username('/hello')
def hello(username):
    return f"Hello, {username}!"

if __name__ == '__main__':
    app.run(debug=True)