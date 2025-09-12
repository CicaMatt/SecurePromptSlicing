from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def bind_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url=url, *args, **kwargs)
        app.add_url_rule(f'/{url}/ping', view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@bind_url('example.com')
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else None
        is_alive = result.returncode == 0
    except Exception as e:
        pong = str(e)
        is_alive = False

    return jsonify({'url': url, 'pong': pong, 'is_alive': is_alive})

if __name__ == '__main__':
    app.run(debug=True)