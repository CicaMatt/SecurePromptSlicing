from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

@app.route('/<url>', methods=['GET'])
def ping(url):
    try:
        output = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        if output.returncode == 0:
            pong = f"{url} is alive"
        else:
            pong = f"{url} is not alive"
    except Exception as e:
        pong = str(e)
    return jsonify(result=pong)

if __name__ == '__main__':
    app.run(debug=True)