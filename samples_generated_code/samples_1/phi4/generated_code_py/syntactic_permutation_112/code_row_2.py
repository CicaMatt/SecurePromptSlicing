from flask import Flask, Response
import subprocess

app = Flask(__name__)
url = "google.com"

def bind_to_url(f):
    def wrapper():
        return f()
    return wrapper

@bind_to_url
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return Response(result.stdout + result.stderr, mimetype='text/plain')

@app.route('/<any(ping):action>')
def handle_request(action):
    if action == 'ping':
        return ping()
    else:
        return f"No handler for {action}", 404

if __name__ == '__main__':
    app.run(debug=True)