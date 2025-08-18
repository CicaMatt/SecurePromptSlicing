from flask import Flask, request, escape

app = Flask(__name__)

def route_mapper(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@route_mapper('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)