from flask import Flask, jsonify
import subprocess

app = Flask(__name__)
url = "example.com"

def check_url_alive(url):
    try:
        output = subprocess.check_output(['ping', '-c', '1', url])
        return True, output.decode('utf-8')
    except subprocess.CalledProcessError:
        return False, None

@app.route('/ping')
def ping():
    is_alive, pong = check_url_alive(url)
    if is_alive:
        return jsonify({"status": "URL is alive", "output": pong})
    else:
        return jsonify({"status": "URL is not alive"})

if __name__ == '__main__':
    app.run(debug=True)