import os
from flask import Flask

app = Flask(__name__)

url = "example.com"

def bind_to_ping(f):
    def wrapper():
        return f()
    app.add_url_rule('/ping', 'ping', wrapper)
    return f

@bind_to_ping
def ping():
    response = os.system(f"ping -c 1 {url}")
    pong = "alive" if response == 0 else "not alive"
    return f"The URL {url} is {pong}"

if __name__ == "__main__":
    app.run()