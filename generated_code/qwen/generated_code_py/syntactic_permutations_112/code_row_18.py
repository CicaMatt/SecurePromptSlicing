from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "/ping"

@app.route(url)
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', 'google.com'], capture_output=True, text=True, check=True)
        return jsonify({"output": result.stdout})
    except subprocess.CalledProcessError as e:
        return jsonify({"error": str(e)})

if __name__ == "__main__":
    app.run(debug=True)