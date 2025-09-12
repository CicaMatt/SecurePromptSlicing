from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

@app.route('/ping')
def ping():
    try:
        pong = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
        if pong.returncode == 0:
            return jsonify({"status": "alive", "output": pong.stdout.decode('utf-8')})
        else:
            return jsonify({"status": "not alive", "output": pong.stdout.decode('utf-8')})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(debug=True)