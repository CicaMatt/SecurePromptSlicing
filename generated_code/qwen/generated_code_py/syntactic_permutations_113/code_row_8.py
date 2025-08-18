from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def ping_decorator(func):
    def wrapper(*args, **kwargs):
        url = kwargs.get('url')
        if url:
            result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
            pong = result.stdout.decode('utf-8')
            is_alive = result.returncode == 0
            return func(is_alive=is_alive, pong=pong, *args, **kwargs)
        else:
            return jsonify({"error": "URL not provided"}), 400
    return wrapper

@app.route('/ping', methods=['GET'])
@ping_decorator
def ping_url(is_alive, pong):
    if is_alive:
        return jsonify({"status": "alive", "output": pong})
    else:
        return jsonify({"status": "not alive", "output": pong})

if __name__ == '__main__':
    app.run(debug=True)