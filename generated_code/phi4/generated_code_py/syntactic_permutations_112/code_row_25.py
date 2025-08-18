from flask import Flask, jsonify
import subprocess
import shlex

app = Flask(__name__)

url = "example.com"

def bind_url(f):
    app.add_url_rule('/ping', 'ping', f)
    return f

@bind_url
def ping():
    command = f"ping -c 4 {shlex.quote(url)}"
    process = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if process.returncode == 0:
        return jsonify({"result": "success", "output": process.stdout})
    else:
        return jsonify({"result": "error", "output": process.stderr})

if __name__ == '__main__':
    app.run(debug=True)