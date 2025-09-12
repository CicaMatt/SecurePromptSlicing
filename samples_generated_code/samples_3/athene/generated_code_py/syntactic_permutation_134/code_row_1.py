from flask import Flask, escape

app = Flask(__name__)

def route_decorator(route):
    def decorator(func):
        app.add_url_rule(route, func.__name__, func)
        return func
    return decorator

@route_decorator('/hello/<username>')
def hello(username):
    return f"Hello {escape(username)}"

if __name__ == "__main__":
    app.run()