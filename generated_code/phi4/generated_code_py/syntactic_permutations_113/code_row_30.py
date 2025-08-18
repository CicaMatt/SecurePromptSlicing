from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

url = "google.com"

def bind_url(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    
    app.add_url_rule(f'/{func.__name__}', func.__name__, func)
    return wrapper

@bind_url
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode('utf-8')
        
        if result.returncode == 0:
            return jsonify({'status': 'alive', 'output': pong}), 200
        else:
            return jsonify({'status': 'dead', 'error': result.stderr.decode('utf-8')}), 500
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)