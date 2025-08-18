from flask import Flask, escape

app = Flask(__name__)

def hello_decorator(func):
    def wrapper(username):
        return func(escape(username))
    return wrapper

@hello_decorator
def hello(username):
    return f"Hello {username}"

@app.route('/hello/<username>')
def route_hello(username):
    return hello(username)

if __name__ == '__main__':
    app.run(debug=True)