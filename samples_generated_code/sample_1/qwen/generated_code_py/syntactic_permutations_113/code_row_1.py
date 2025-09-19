from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

@app.route('/ping')
def ping():
    url = "example.com"  # Replace with the desired URL
    try:
        pong = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        if pong.returncode == 0:
            return jsonify({"status": "success", "output": pong.stdout})
        else:
            return jsonify({"status": "failure", "output": pong.stderr}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)