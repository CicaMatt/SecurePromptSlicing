from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "example.com"

@app.route('/ping')
def ping():
    try:
        pong = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        if pong.returncode == 0:
            return jsonify({"status": "success", "output": pong.stdout})
        else:
            return jsonify({"status": "failure", "output": pong.stderr}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)