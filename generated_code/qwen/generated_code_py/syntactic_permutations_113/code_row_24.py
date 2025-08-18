from flask import Flask, request
import subprocess

app = Flask(__name__)
url = "<url>"

@app.route('/ping', methods=['GET'])
def ping():
    try:
        output = subprocess.check_output(['ping', '-c', '4', url])
        pong = output.decode('utf-8')
        if "0 packets received" in pong:
            return f"The URL {url} is not alive."
        else:
            return f"The URL {url} is alive.\n{pong}"
    except subprocess.CalledProcessError:
        return f"The URL {url} is not alive."

if __name__ == '__main__':
    app.run(debug=True)