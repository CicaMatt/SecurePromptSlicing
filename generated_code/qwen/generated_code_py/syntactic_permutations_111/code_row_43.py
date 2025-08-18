from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    try:
        # Running the ping command and capturing the output
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return output
    except subprocess.CalledProcessError as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)