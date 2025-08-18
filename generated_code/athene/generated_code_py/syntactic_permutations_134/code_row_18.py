from flask import Flask, escape

app = Flask(__name__)

def route(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, lambda: func(escape(username)), methods=['GET'])
        return func
    return decorator

@route('/hello/<username>')
def hello(username):
    return f"Hello, {username}!"

if __name__ == "__main__":
    app.run(debug=True)