from flask import Flask, escape

app = Flask(__name__)

def route(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, lambda: func(escape(username)))
        return func
    return decorator

@route('/hello/<username>')
def hello(username):
    return f'Hello {username}'

# Simulate the call to the function as if it was a request
with app.test_request_context():
    username = 'World'
    print(app.dispatch_request())