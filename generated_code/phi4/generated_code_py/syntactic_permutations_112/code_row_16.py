from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

url = "8.8.8.8"  # Example IP address for Google's DNS server

def ping_decorator(func):
    def wrapper(*args, **kwargs):
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        return func(result.stdout + result.stderr)
    return wrapper

@app.route('/ping')
@ping_decorator
def ping():
    return jsonify({'output': request.data.decode('utf-8')})

if __name__ == '__main__':
    app.run(debug=True)