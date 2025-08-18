from flask import Flask, escape

app = Flask(__name__)

def route(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, lambda: func(escape(username)))
        return func
    return decorator

@route('/<username>')
def greet_user(username):
    return f'Hello {username}'

if __name__ == '__main__':
    app.run()