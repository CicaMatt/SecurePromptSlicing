from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def ping_url(func):
    def wrapper(url):
        try:
            pong = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
            if pong.returncode == 0:
                return func(True, pong.stdout)
            else:
                return func(False, pong.stderr)
        except Exception as e:
            return func(False, str(e))
    return wrapper

@app.route('/ping/<url>')
@ping_url
def ping(url, is_alive, output):
    if is_alive:
        return jsonify({"status": "Alive", "output": output})
    else:
        return jsonify({"status": "Not Alive", "output": output})

if __name__ == '__main__':
    app.run(debug=True)