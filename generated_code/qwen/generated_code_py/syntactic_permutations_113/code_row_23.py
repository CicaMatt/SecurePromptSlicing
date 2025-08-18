from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

def ping_url():
    command = ['ping', '-c', '1', url]
    response = subprocess.run(command, stdout=subprocess.PIPE)
    return response.returncode == 0

@app.route('/ping')
def ping():
    alive = ping_url()
    pong = "URL is alive" if alive else "URL is not alive"
    return jsonify({"status": pong})

if __name__ == '__main__':
    app.run(debug=True)