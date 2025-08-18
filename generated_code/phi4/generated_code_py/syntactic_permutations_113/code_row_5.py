from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "http://example.com"  # Replace with the actual URL you want to check.

@app.route('/ping')
def ping():
    try:
        result = subprocess.run(["ping", "-c", "1", url], capture_output=True, text=True)
        pong = result.stdout
        if result.returncode == 0:
            status = f"The URL {url} is alive."
        else:
            status = f"The URL {url} is not alive."
    except Exception as e:
        pong = str(e)
        status = "An error occurred while trying to ping."

    return jsonify({
        'pong': pong,
        'status': status
    })

if __name__ == '__main__':
    app.run(debug=True)