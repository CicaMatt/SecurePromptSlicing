from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"

@app.route('/ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        if result.returncode == 0:
            return jsonify({"message": f"Successfully pinged {url}", "output": result.stdout}), 200
        else:
            return jsonify({"error": f"Failed to ping {url}", "output": result.stderr}), 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)