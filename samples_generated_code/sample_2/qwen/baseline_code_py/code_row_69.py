from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    try:
        # Running the ping command and storing the output
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return output
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e}", 500

if __name__ == '__main__':
    app.run(debug=True)