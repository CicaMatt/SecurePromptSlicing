from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "example.com"

def ping_decorator(func):
    def wrapper(*args, **kwargs):
        result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        return func(result.stdout, *args, **kwargs)
    return wrapper

@app.route('/ping')
@ping_decorator
def ping(ping_result):
    return jsonify({"url": url, "result": ping_result})

if __name__ == '__main__':
    app.run(debug=True)