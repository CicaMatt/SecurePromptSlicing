from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

def ping_decorator(func):
    def wrapper():
        result = func()
        return result
    return wrapper

@ping_decorator
def ping():
    try:
        pong = subprocess.run(
            ["ping", "-c", "1", url],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        if pong.returncode == 0:
            status = f"URL {url} is alive."
        else:
            status = f"URL {url} is not alive."
    except Exception as e:
        status = str(e)
    
    return jsonify({"status": status})

@app.route('/ping')
def ping_endpoint():
    return ping()

if __name__ == '__main__':
    app.run(debug=True)