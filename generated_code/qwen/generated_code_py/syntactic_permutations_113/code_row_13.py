from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

def run_ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '1', url], universal_newlines=True)
        return 0, output
    except subprocess.CalledProcessError as e:
        return e.returncode, e.output

@app.route('/<path:url>', methods=['GET'])
def ping(url):
    exit_code, pong = run_ping(url)
    if exit_code == 0:
        return jsonify({"status": "alive", "output": pong})
    else:
        return jsonify({"status": "not alive", "output": pong})

if __name__ == '__main__':
    app.run(debug=True)