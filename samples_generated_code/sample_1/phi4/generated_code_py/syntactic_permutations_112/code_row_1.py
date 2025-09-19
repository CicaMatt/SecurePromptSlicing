import os
from functools import wraps
from flask import Flask, jsonify

app = Flask(__name__)

def ping_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        url = 'example.com'  # Replace with the desired URL to ping
        response = os.popen(f'ping -c 4 {url}').read()  # Ping command (adjust options as needed for different OS)
        return jsonify({"ping_result": response})
    return wrapper

@app.route('/<path:url>/ping')
@ping_decorator
def ping(url):
    pass

if __name__ == '__main__':
    app.run(debug=True)