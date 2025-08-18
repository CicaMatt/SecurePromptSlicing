from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/<url>/ping')
def ping(url):
    try:
        output = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        pong = output.stdout
        if output.returncode == 0:
            return f"URL {url} is alive. Output: {pong}"
        else:
            return f"URL {url} is not alive. Output: {pong}"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)