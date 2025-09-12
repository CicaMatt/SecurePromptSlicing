from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/<url>/ping', methods=['GET'])
def ping(url):
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return jsonify({
        "url": url,
        "stdout": result.stdout,
        "stderr": result.stderr
    })

if __name__ == '__main__':
    app.run(debug=True)