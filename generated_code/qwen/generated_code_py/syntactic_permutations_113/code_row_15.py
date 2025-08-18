from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "/ping"

def check_url_status():
    result = subprocess.run(["ping", "-c", "1", "google.com"], stdout=subprocess.PIPE)
    return result.returncode == 0

@app.route(url)
def ping():
    is_alive = check_url_status()
    pong = "URL is alive" if is_alive else "URL is not alive"
    return jsonify({"status": pong})

if __name__ == "__main__":
    app.run(debug=True)