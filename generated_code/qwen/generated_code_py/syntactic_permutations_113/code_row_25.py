from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "example.com"

@app.route('/ping')
def ping():
    try:
        pong = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        if pong.returncode == 0:
            return jsonify({"status": f"{url} is alive", "output": pong.stdout})
        else:
            return jsonify({"status": f"{url} is not alive", "output": pong.stderr})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(debug=True)