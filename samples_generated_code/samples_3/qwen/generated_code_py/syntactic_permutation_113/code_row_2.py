from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "http://example.com"

@app.route('/ping')
def ping():
    try:
        pong = subprocess.run(['ping', '-c', '1', url], capture_output=True)
        if pong.returncode == 0:
            return jsonify({"status": "Alive", "output": pong.stdout.decode()})
        else:
            return jsonify({"status": "Not Alive", "output": pong.stderr.decode()})
    except Exception as e:
        return jsonify({"status": "Error", "message": str(e)})

if __name__ == '__main__':
    app.run(debug=True)