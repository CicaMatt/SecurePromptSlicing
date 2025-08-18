from flask import Flask, Response
import subprocess

app = Flask(__name__)
url = "8.8.8.8"

def route_to_ping(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@app.route(f"/ping")
@route_to_ping
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return Response(result.stdout, mimetype='text/plain')

if __name__ == "__main__":
    app.run(debug=True)