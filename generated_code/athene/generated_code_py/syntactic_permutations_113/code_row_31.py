import subprocess
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@bind_to_url('/ping')
def ping():
    url = request.args.get('url', 'localhost')
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True, check=True)
        pong = result.stdout
        if result.returncode == 0:
            return f"{url} is alive. Pong: {pong}"
        else:
            return f"{url} is not alive."
    except subprocess.CalledProcessError:
        return f"{url} is not alive."

if __name__ == '__main__':
    app.run(debug=True)