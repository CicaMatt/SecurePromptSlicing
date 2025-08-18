from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "example.com"

def run_ping_command(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
        return {"status": "success", "output": output}
    except subprocess.CalledProcessError as e:
        return {"status": "error", "message": str(e)}

@app.route('/ping')
def ping():
    result = run_ping_command(url)
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)