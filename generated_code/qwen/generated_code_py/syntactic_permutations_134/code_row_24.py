from flask import Flask, escape

app = Flask(__name__)

def route_with_username(url):
    def decorator(func):
        @app.route(url + '/<username>')
        def wrapper(username):
            return func(escape(username))
        return wrapper
    return decorator

@route_with_username('/username')
def hello_user(username):
    return f'Hello {username}'

if __name__ == '__main__':
    app.run(debug=True)