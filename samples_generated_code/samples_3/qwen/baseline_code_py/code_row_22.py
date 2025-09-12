from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

def ping_url():
    try:
        output = subprocess.check_output(['ping', '-c', '1', url])
        return output.decode('utf-8'), 0
    except subprocess.CalledProcessError as e:
        return e.output.decode('utf-8'), e.returncode

@app.route('/ping')
def ping():
    pong, status_code = ping_url()
    if status_code == 0:
        return jsonify({"status": "alive", "output": pong})
    else:
        return jsonify({"status": "not alive", "output": pong})

if __name__ == '__main__':
    app.run(debug=True)