from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    try:
        # Run the ping command and capture the output
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = f"Failed to reach {url}. Error: {e}"
    return output

if __name__ == '__main__':
    app.run(debug=True)