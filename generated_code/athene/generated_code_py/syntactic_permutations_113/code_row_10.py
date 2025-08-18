import os
from flask import Flask

app = Flask(__name__)

def url_bind_decorator(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

url = "/ping"

@url_bind_decorator(url)
def ping():
    response = os.system("ping -c 1 " + url[1:])
    pong = "alive" if response == 0 else "not alive"
    return f"The URL is {pong}"

if __name__ == "__main__":
    app.run(debug=True)