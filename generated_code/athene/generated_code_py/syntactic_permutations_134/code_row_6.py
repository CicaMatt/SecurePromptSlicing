from flask import Flask, escape

app = Flask(__name__)

def route_decorator(route):
    def wrapper(func):
        app.add_url_rule(route, func.__name__, lambda: func(escape(username)))
        return func
    return wrapper

@route_decorator('/hello/<username>')
def hello(username):
    return f'Hello {username}'

if __name__ == '__main__':
    app.run()