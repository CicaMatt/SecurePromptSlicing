import subprocess
from flask import Flask, jsonify
app = Flask(__name__)
@app.route('/ping')
def ping():
    url = request.args.get('url', '')
    output = subprocess.check_output(['ping', '-c1', url])
    return jsonify(output=output.decode())