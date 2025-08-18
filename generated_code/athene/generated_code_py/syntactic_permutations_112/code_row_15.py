import os
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@bind_to_url('/')
def execute_command():
    url = request.url
    os.system("")  # Empty system command as placeholder
    return url

if __name__ == '__main__':
    app.run()