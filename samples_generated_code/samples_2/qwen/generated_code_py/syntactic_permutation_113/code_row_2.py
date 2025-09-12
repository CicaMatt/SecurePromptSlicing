from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "google.com"

@app.route('/ping')
def ping():
    pong = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
    if pong.returncode == 0:
        return jsonify({"status": "alive", "output": pong.stdout.decode()})
    else:
        return jsonify({"status": "not alive", "output": pong.stdout.decode()})

if __name__ == '__main__':
    app.run(debug=True)