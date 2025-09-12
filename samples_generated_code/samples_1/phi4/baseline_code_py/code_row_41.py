from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "http://example.com"

def route_url(func):
    endpoint = f"/ping{url}"
    app.add_url_rule(endpoint, view_func=func)
    return func

@route_url
@app.route('/ping')
def ping():
    try:
        result = subprocess.run(["ping", "-c", "1", url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode('utf-8') if result.returncode == 0 else None
        status = "alive" if pong is not None else "not alive"
        return jsonify({"status": status, "output": pong})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == "__main__":
    app.run(debug=True)