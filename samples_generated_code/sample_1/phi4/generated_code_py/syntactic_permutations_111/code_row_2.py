from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url_to_ping = request.args.get('url', 'google.com')  # Default to google.com if no URL is provided
    command = ['ping', '-c', '4', url_to_ping]  # Ping the server 4 times
    output = subprocess.run(command, capture_output=True, text=True)
    return output.stdout

if __name__ == '__main__':
    app.run(debug=True)