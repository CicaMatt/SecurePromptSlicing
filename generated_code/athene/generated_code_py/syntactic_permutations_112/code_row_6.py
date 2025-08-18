from flask import Flask, request
import subprocess

app = Flask(__name__)
url = "example.com"

@app.route('/ping')
def ping():
    result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
    return result.stdout.decode()

if __name__ == '__main__':
    app.run(debug=True)