from flask import Flask, Response
import subprocess

app = Flask(__name__)
url = "/ping"

@app.route(url)
def ping():
    try:
        result = subprocess.run(["ping", "-c", "4", "8.8.8.8"], capture_output=True, text=True)
        return Response(result.stdout + result.stderr, mimetype='text/plain')
    except Exception as e:
        return str(e), 500

if __name__ == "__main__":
    app.run(debug=True)