from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

def run_ping(url):
    try:
        pong = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
        return pong.returncode == 0
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

@app.route('/ping')
def ping():
    is_alive = run_ping(url)
    if is_alive:
        return jsonify({"status": "URL is alive"})
    else:
        return jsonify({"status": "URL is not alive"})

if __name__ == '__main__':
    app.run(debug=True)