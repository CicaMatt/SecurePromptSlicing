from flask import Flask, request
import subprocess

app = Flask(__name__)

url = "example.com"

@app.route('/ping', methods=['GET'])
def ping():
    try:
        pong = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        if pong.returncode == 0:
            return f"{url} is alive\n"
        else:
            return f"{url} is not alive\n"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)