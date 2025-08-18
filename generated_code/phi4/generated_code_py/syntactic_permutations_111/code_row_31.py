from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(url)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@trigger_url('/ping')
def ping(url):
    url_param = request.args.get('url')
    if not url_param:
        return "Missing 'url' parameter", 400
    
    output = subprocess.run(['ping', '-c', '4', url_param], capture_output=True, text=True)
    return output.stdout

if __name__ == '__main__':
    app.run(debug=True)