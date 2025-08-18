from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url_rule):
    def decorator(func):
        app.add_url_rule(url_rule, func.__name__, func)
        return func
    return decorator

@trigger_url('/ping')
def ping():
    url = request.args.get('url', '')
    if not url:
        return "URL parameter is required."
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}"
    
    return output

if __name__ == '__main__':
    app.run(debug=True)