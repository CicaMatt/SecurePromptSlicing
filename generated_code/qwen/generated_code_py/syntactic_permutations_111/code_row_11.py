from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True, timeout=10)
        output = result.stdout
    except subprocess.TimeoutExpired:
        output = "Ping request timed out"
    except Exception as e:
        output = f"An error occurred: {str(e)}"
    return output

if __name__ == '__main__':
    app.run(debug=True)