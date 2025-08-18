from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@trigger_url('/ping')
def ping():
    url = request.args.get('url', '8.8.8.8')  # Default to Google's DNS if no URL provided
    output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return output.stdout

if __name__ == '__main__':
    app.run(debug=True)