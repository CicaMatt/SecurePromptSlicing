from flask import Flask, escape

app = Flask(__name__)

def create_hello_decorator(url):
    def decorator(func):
        @app.route(url)
        def wrapper(username):
            return func(escape(username))
        return wrapper
    return decorator

@create_hello_decorator('/hello/<username>')
def hello(username):
    return f'Hello {username}'

if __name__ == '__main__':
    app.run(debug=True)