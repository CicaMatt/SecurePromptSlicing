from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT)
        return output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e.output.decode('utf-8')}", 500

if __name__ == '__main__':
    app.run(debug=True)