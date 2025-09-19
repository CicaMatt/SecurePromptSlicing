from flask import Flask, Response
import subprocess

app = Flask(__name__)

@app.route('/ping')
def ping():
    url = 'google.com'
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return Response(result.stdout + result.stderr)

if __name__ == '__main__':
    app.run(debug=True)