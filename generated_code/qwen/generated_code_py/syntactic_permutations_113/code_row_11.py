from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "/check"

def check_url_status():
    try:
        pong = subprocess.run([""], capture_output=True)
        if pong.returncode == 0:
            return "URL is alive"
        else:
            return "URL is not alive"
    except Exception as e:
        return f"An error occurred: {str(e)}"

@app.route(url)
def status():
    result = check_url_status()
    return jsonify(result=result)

if __name__ == "__main__":
    app.run(debug=True)