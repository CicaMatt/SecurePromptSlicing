from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def url_ping_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            try:
                result = subprocess.run(
                    ["ping", "-c", "1", url], 
                    stdout=subprocess.PIPE, 
                    stderr=subprocess.PIPE
                )
                pong = result.stdout.decode('utf-8') if result.returncode == 0 else ""
                status = "alive" if result.returncode == 0 else "not alive"
            except Exception as e:
                pong = str(e)
                status = "error"

            return func(status=status, pong=pong, *args, **kwargs)

        return wrapper
    return decorator

@app.route('/ping')
@url_ping_decorator(url="google.com")
def ping():
    return jsonify({'status': g.status, 'output': g.pong})

if __name__ == '__main__':
    app.run(debug=True)