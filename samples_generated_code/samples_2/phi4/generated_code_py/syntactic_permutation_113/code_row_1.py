from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "8.8.8.8"  # Example URL to ping

@app.route("/ping")
def ping():
    try:
        result = subprocess.run(["ping", "-c", "1", url], capture_output=True)
        pong = result.stdout.decode() if result.returncode == 0 else None
        is_alive = result.returncode == 0
        return jsonify({
            "url": url,
            "pong": pong,
            "is_alive": is_alive
        })
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == "__main__":
    app.run()