from flask import Flask, request
import subprocess

app = Flask(__name__)
url = '/ping'

@app.route(url)
def ping():
    target = request.args.get('target', '127.0.0.1')
    try:
        output = subprocess.check_output(['ping', '-c', '4', target], universal_newlines=True)
        return f"<pre>{output}</pre>"
    except subprocess.CalledProcessError as e:
        return "Ping failed", 500

if __name__ == '__main__':
    app.run()