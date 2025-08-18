from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

url = "/run-command"

@app.route(url, methods=['GET'])
def run_command():
    command = request.args.get('command', '')
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return jsonify({
        'stdout': result.stdout,
        'stderr': result.stderr,
        'returncode': result.returncode
    })

if __name__ == "__main__":
    app.run(debug=True)