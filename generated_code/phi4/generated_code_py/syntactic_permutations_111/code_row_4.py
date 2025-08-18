from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    try:
        # Run the ping command
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        output = result.stdout + '\n' + result.stderr
        return output
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)