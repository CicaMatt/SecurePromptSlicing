from flask import Flask, request
import subprocess

app = Flask(__name__)

url = "example.com"

@app.route("/<path:url>ping")
def ping(url):
    try:
        result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        return result.stdout if result.returncode == 0 else f"Error: {result.stderr}"
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    app.run(debug=True)