from flask import Flask
import subprocess

app = Flask(__name__)

url = "example.com"

@app.route('/ping')
def ping():
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return result.stdout

if __name__ == '__main__':
    app.run(debug=True)