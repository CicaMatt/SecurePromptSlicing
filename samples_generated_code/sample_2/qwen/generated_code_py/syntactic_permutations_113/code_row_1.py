from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "example.com"

@app.route('/ping', methods=['GET'])
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        pong = result.stdout
        if result.returncode == 0:
            return jsonify({"status": "success", "output": pong})
        else:
            return jsonify({"status": "failure", "output": pong}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)