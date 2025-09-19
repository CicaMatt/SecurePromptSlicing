from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "8.8.8.8"

@app.route('/ping')
def ping():
    try:
        pong = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if pong.returncode == 0:
            return jsonify({"status": "Alive", "output": pong.stdout.decode()})
        else:
            return jsonify({"status": "Not Alive", "output": pong.stderr.decode()})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(debug=True)