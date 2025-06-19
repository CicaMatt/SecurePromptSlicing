import re
from functools import wraps
from flask import Flask, escape

app = Flask(__name__)

def process_url(url):
    """
    Return a decorator that takes in a function and returns a new function that 
    processes the URL before calling the original function.
    """
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            # process the url
            url_parts = re.match(r'^/hello/(?P<username>.*)$', url)
            if not url_parts:
                return 'Incorrect URL format', 404
            username = url_parts.group('username')
            # call the original function with the processed url
            return func(username, *args, **kwargs)
        return wrapper
    return decorator

@app.route('/hello/<username>', methods=['GET'])
@process_url(url='/hello/<username>')
def hello(username):
    """
    Return a greeting for the username.
    """
    return f'Hello, {escape(username)}!'
if __name__ == '__main__':
    app.run()