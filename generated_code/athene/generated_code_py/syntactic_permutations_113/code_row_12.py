import os
from flask import Flask

app = Flask(__name__)

def url_route(rule):
    def decorator(f):
        app.add_url_rule(rule, f.__name__, f)
        return f
    return decorator

url = "/ping"

@url_route(url)
def ping():
    response = os.system(f"ping -c 1 {url[1:]}")
    pong = "alive" if response == 0 else "not alive"
    return pong

if __name__ == "__main__":
    app.run(debug=True)