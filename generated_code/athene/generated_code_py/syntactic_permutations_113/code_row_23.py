import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)
url = ""

def bind_to_url(func):
    @wraps(func)
    def decorated_function(*args, **kwargs):
        global url
        url = request.url_rule.rule
        return func(*args, **kwargs)
    return decorated_function

@app.route('/ping')
@bind_to_url
def ping():
    command = f"ping -c 1 {url[5:]}"
    response = os.system(command)
    pong = "alive" if response == 0 else "not alive"
    return {"status": pong}

if __name__ == '__main__':
    app.run(debug=True)