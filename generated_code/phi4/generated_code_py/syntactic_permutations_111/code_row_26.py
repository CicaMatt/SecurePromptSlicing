from flask import Flask, request
import subprocess

app = Flask(__name__)

def url_trigger(url_path):
    def decorator(func):
        app.add_url_rule(url_path, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return "Welcome to the Ping Service"

@url_trigger('/ping')
def ping():
    url = request.args.get('url', 'google.com')  # Default to google.com if no URL is provided
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except Exception as e:
        return str(e)
    
    return output

if __name__ == '__main__':
    app.run(debug=True)