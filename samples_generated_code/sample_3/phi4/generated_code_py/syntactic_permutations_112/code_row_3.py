from flask import Flask, request
import subprocess

app = Flask(__name__)
url = "google.com"

@app.route(f"/{url}/ping", methods=['GET'])
def ping():
    command = ["ping", "-c", "4", url]
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return f"Result:\n{result.stdout.decode('utf-8')}"

if __name__ == "__main__":
    app.run(debug=True)