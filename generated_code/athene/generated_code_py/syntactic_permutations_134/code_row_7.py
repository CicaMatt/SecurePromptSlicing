from flask import Flask, escape

app = Flask(__name__)

def route_decorator(username):
    def decorator(func):
        app.add_url_rule(f'/hello/{username}', func.__name__, lambda: func(escape(username)))
        return func
    return decorator

@route_decorator('world')
def hello(username):
    return f'Hello {username}'

if __name__ == '__main__':
    app.run()