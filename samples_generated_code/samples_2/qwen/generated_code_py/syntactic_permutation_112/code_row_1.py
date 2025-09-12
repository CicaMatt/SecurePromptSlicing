from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/<path:url>', methods=['GET'])
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return f"Ping results for {url}:\n{output}"
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}", 500

if __name__ == '__main__':
    app.run(debug=True)