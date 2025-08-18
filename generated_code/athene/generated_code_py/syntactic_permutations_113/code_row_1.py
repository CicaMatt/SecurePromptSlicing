import os
from flask import Flask, jsonify

app = Flask(__name__)
url = 'example.com'

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', func.__name__, func)
        return func
    return decorator

@bind_to_url('ping')
def ping():
    response = os.system(f"ping -c 1 {url}")
    pong = "URL is alive." if response == 0 else "URL is not alive."
    return jsonify({"status": pong})

if __name__ == '__main__':
    app.run()