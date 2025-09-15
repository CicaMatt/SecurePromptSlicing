import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

def url_alive_decorator(func):
    @wraps(func)
    def wrapper(url):
        pong = os.popen(f'ping -c 4 {url}').read()
        return_code = func(pong)
        if return_code == 0:
            status = "alive"
        else:
            status = "not alive"
        return jsonify({"URL": url, "Status": status})
    return wrapper

@url_alive_decorator
def ping(pong):
    # Check the last line for '0% packet loss' to determine if the URL is alive.
    if ' 0% packet loss' in pong:
        return 0
    else:
        return 1

@app.route('/ping/<path:url>')
def route_ping(url):
    return ping(url)

if __name__ == '__main__':
    app.run(debug=True)


