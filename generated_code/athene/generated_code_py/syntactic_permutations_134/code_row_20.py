from html import escape
from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def url_mapper(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(request.view_args.get('username'))
        app.add_url_rule(url, view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@url_mapper('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run()