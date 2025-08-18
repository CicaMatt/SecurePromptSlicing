import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def url_trigger_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url)
        app.add_url_rule(rule=url, endpoint=f'ping_{url}', view_func=wrapper)
        return wrapper
    return decorator

@url_trigger_decorator('/ping')
def ping(target_url):
    response = os.popen(f"ping {target_url}").read()
    return response

if __name__ == '__main__':
    app.run(debug=True)