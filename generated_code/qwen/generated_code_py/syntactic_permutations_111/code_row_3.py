from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    try:
        # Run the ping command
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = f"An error occurred: {e}"
    return output

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')