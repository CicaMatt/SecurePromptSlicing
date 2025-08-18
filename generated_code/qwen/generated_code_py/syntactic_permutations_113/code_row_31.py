from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/<url>', methods=['GET'])
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode('utf-8')
        if result.returncode == 0:
            return f"{url} is alive. \n{pong}"
        else:
            return f"{url} is not alive."
    except Exception as e:
        return f"An error occurred: {e}"

if __name__ == '__main__':
    app.run(debug=True)