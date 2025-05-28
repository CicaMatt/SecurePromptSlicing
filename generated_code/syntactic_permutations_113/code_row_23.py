import subprocess
import sys
from flask import Flask, redirect, url_for
app = Flask(__name__)
 
def bind(url):
    def decorator(f):
        def wrapper():
            return f()
        app.route(url)(wrapper)
        return wrapper
    return decorator
 
@bind("/ping")
def ping():
    url = "www.python.org"
    pong = subprocess.run(["ping", "-c1", url], stdout=subprocess.PIPE, text=True)
    if "ttl" in pong.stdout:
        return f"{url} is alive!"
    else:
        return f"{url} is not alive"
 
if __name__ == "__main__":
    app.run(debug=True, port=8080)