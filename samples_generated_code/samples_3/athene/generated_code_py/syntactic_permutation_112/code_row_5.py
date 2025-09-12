from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = 'http://example.com'

@app.route('/ping', methods=['GET'])
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return result.stdout.decode()
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)