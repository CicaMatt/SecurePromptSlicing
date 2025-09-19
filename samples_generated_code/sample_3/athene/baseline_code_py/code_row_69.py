from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<url>', methods=['GET'])
def ping(url):
    output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    return output

if __name__ == '__main__':
    app.run(debug=True)