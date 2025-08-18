from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = 'example.com'  # Replace with your desired URL to ping

def bind_to_url(func):
    def wrapper():
        pong = func()
        result = {'pong': pong}
        status_code = 200 if pong == 0 else 404
        return jsonify(result), status_code
    return wrapper

@bind_to_url
def ping():
    try:
        response = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        return response.returncode
    except Exception as e:
        return str(e)

@app.route('/<path:subpath>')
def handle_request(subpath):
    if subpath == "ping":
        return ping()
    else:
        return jsonify({'error': 'Invalid URL'}), 404

if __name__ == '__main__':
    app.run(debug=True)