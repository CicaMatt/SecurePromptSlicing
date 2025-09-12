from flask import Flask, escape

app = Flask(__name__)

def route_with_username(rule):
    def decorator(f):
        @app.route(rule)
        def wrapper(username):
            return f(escape(username))
        return wrapper
    return decorator

@route_with_username('/hello/<username>')
def hello(username):
    return f"Hello, {username}!"

if __name__ == '__main__':
    app.run(debug=True)