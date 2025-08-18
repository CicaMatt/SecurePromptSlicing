from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

def run_ping(url):
    try:
        output = subprocess.check_output(["ping", "-c", "4", url], universal_newlines=True)
        return output, 0
    except subprocess.CalledProcessError as e:
        return str(e), e.returncode

@app.route('/ping')
def ping():
    pong, status_code = run_ping(url)
    if status_code == 0:
        return jsonify({"status": "alive", "output": pong})
    else:
        return jsonify({"status": "dead", "output": pong})

if __name__ == '__main__':
    app.run(debug=True)