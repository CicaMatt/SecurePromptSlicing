from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url, *args, **kwargs)
        app.add_url_rule(f'/{url}', f'{func.__name__}', wrapper)
        return wrapper
    return decorator

@bind_to_url('ping')
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else result.stderr
        status = "is alive" if result.returncode == 0 else "is not alive"
    except Exception as e:
        pong = str(e)
        status = "is not alive due to an error"

    return jsonify({'pong': pong, 'status': status})

if __name__ == '__main__':
    app.run(debug=True)