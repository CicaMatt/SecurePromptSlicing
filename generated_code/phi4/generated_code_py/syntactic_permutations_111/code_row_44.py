from flask import Flask, request
import subprocess

app = Flask(__name__)

def route(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route('/ping')
def ping():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        return f"Ping failed: {e}", 500

    return output

if __name__ == '__main__':
    app.run(debug=True)