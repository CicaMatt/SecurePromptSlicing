from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = '8.8.8.8'  # Example ping URL (Google's public DNS)

def ping_decorator(func):
    def wrapper(*args, **kwargs):
        result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE)
        response = {
            'output': result.stdout.decode('utf-8'),
            'url': url
        }
        return jsonify(response)
    return wrapper

@app.route('/ping')
@ping_decorator
def ping():
    pass

if __name__ == '__main__':
    app.run(debug=True)