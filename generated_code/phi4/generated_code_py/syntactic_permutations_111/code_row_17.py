from flask import Flask, request
import subprocess

app = Flask(__name__)

def url_trigger(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@url_trigger('/ping')
def ping():
    target_url = request.args.get('url', '')
    if not target_url:
        return "URL parameter is missing", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', target_url], text=True)
    except subprocess.CalledProcessError as e:
        return str(e), 500
    return output

if __name__ == "__main__":
    app.run(debug=True)