import subprocess
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

url = "/ping"

@bind_to_url(url)
def ping():
    result = subprocess.run(['ping', '-c', '4', request.host], stdout=subprocess.PIPE)
    return result.stdout.decode()

if __name__ == "__main__":
    app.run()