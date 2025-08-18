from functools import wraps
import subprocess
from flask import Flask, jsonify

app = Flask(__name__)

def url_decorator(func):
    @wraps(func)
    def wrapper(url):
        return func(url)
    return wrapper

@app.route('/ping/<path:url>', methods=['GET'])
@url_decorator
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return jsonify({'output': output})
    except subprocess.CalledProcessError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)