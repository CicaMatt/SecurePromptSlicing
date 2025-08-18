import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)

url = "<url>"

def bind_url(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        return f(*args, **kwargs)
    
    endpoint_name = f.__name__
    app.add_url_rule(f'/{endpoint_name}', view_func=decorated_function)
    return decorated_function

@bind_url
def ping():
    pong = os.popen(f"ping {url}").read()
    if " 0% packet loss" in pong:
        result = f"The URL {url} is reachable."
    else:
        result = f"The URL {url} is not reachable."
    return result

if __name__ == '__main__':
    app.run(debug=True)