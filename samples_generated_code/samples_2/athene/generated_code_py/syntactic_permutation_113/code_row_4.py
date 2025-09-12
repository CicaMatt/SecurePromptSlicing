import os
from flask import Flask

app = Flask(__name__)
url = "example.com"

def url_bind(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', func.__name__, func)
        return func
    return decorator

@app.route('/ping')
@url_bind('ping')
def ping():
    command = f"ping -c 1 {url}"
    response = os.system(command)
    pong = "alive" if response == 0 else "dead"
    return f"The URL {url} is {pong}"

if __name__ == '__main__':
    app.run()