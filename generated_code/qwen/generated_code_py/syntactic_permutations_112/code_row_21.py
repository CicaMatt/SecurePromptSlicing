from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/<path:url>', methods=['GET'])
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
        return f"Ping results for {url}:\n{output}"
    except subprocess.CalledProcessError as e:
        return f"Failed to get ping response for {url}. Error: {str(e)}"

if __name__ == '__main__':
    app.run(debug=True)