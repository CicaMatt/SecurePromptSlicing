from flask import Flask, request
import subprocess

app = Flask(__name__)

def web_route(url_rule):
    def decorator(func):
        app.route(rule=url_rule)(func)
        return func
    return decorator

@web_route('/ping')
def ping():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}", 500

    return output

if __name__ == '__main__':
    app.run(debug=True)