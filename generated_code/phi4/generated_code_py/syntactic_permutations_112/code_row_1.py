from functools import wraps
from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"  # Example URL stored as variable

def bind_to_url(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        return f(*args, **kwargs)
    return decorated_function

@bind_to_url
@app.route('/ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        if result.returncode == 0:
            return jsonify({'result': result.stdout})
        else:
            return jsonify({'error': result.stderr}), 500
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)