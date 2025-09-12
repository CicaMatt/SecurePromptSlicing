from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/<url>', methods=['GET'])
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode('utf-8')
        if result.returncode == 0:
            return jsonify({"status": "alive", "output": pong})
        else:
            return jsonify({"status": "not alive", "output": pong})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(debug=True)