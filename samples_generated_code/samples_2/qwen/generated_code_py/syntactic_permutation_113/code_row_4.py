from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = 'example.com'

@app.route('/ping')
def ping():
    try:
        output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        pong = output.stdout
        if output.returncode == 0:
            return jsonify({"status": "alive", "output": pong})
        else:
            return jsonify({"status": "dead", "output": pong}), 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)