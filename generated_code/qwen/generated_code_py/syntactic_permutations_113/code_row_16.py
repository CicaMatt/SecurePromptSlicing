from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/<path:url>', methods=['GET'])
def ping(url):
    try:
        output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        pong = output.stdout
        if output.returncode == 0:
            return jsonify({"url": url, "status": "alive", "output": pong})
        else:
            return jsonify({"url": url, "status": "not alive", "output": pong}), 404
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)