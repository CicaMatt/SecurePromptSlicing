from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "<url>"

def bind_url(f):
    def wrapped():
        return f()
    app.route('/ping')(wrapped)
    return wrapped

@bind_url
def ping():
    try:
        pong = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        if pong.returncode == 0:
            status = "alive"
        else:
            status = "not alive"
        result = {"url": url, "status": status}
    except Exception as e:
        result = {"error": str(e)}
    
    return jsonify(result)

if __name__ == "__main__":
    app.run(debug=True)