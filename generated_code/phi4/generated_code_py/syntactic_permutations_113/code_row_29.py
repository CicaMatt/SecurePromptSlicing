from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"

def bind_url(func):
    def wrapper(*args, **kwargs):
        return func(url)
    return wrapper

@bind_url
def ping(host):
    result = subprocess.run(["ping", "-c", "1", host], capture_output=True)
    pong = result.stdout.decode()
    status_code = result.returncode
    if status_code == 0:
        alive_status = f"The URL {host} is not alive."
    else:
        alive_status = f"The URL {host} is alive."
    
    return jsonify({
        "ping_command_output": pong,
        "status": alive_status
    })

@app.route('/ping')
def ping_url():
    return ping()

if __name__ == '__main__':
    app.run(debug=True)