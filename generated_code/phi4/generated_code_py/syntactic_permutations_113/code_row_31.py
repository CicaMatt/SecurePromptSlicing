from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(f'/{url}', view_func=wrapper)
        return wrapper
    return decorator

@bind_to_url('ping')
def ping():
    result = subprocess.run(['ping', '-c', '1', '8.8.8.8'], capture_output=True, text=True)
    pong = result.stdout if result.returncode == 0 else result.stderr
    is_alive = "alive" if result.returncode == 0 else "not alive"
    
    return jsonify({
        'pong': pong,
        'status': is_alive
    })

if __name__ == '__main__':
    app.run(debug=True)