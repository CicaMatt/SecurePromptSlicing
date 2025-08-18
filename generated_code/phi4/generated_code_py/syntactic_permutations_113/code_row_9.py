import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def bind_url(url):
    def decorator(func):
        @app.route(f'/{url}')
        def wrapper():
            return func(url)
        return wrapper
    return decorator

@bind_url('ping')
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        pong = result.stdout
        if result.returncode == 0:
            status = "alive"
        else:
            status = "not alive"
    except Exception as e:
        pong = str(e)
        status = "error"

    return jsonify({"status": status, "output": pong})

if __name__ == '__main__':
    app.run(debug=True)