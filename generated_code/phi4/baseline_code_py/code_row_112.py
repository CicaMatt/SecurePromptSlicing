from flask import Flask, request
import subprocess

app = Flask(__name__)
url = "8.8.8.8"  # Example URL/IP address for ping

def bind_to_url(route):
    def decorator(func):
        app.route(route)(func)
        return func
    return decorator

@bind_to_url('/ping')
def ping():
    response = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return response.stdout + "\n" + response.stderr

if __name__ == '__main__':
    app.run(debug=True)