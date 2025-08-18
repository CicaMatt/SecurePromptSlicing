from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

@app.route('/ping')
def ping():
    try:
        pong = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        if pong.returncode == 0:
            return jsonify({"status": "URL is alive", "output": pong.stdout})
        else:
            return jsonify({"status": "URL is not alive", "output": pong.stderr})
    except Exception as e:
        return jsonify({"status": "An error occurred", "error": str(e)})

if __name__ == '__main__':
    app.run(debug=True)