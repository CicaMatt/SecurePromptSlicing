from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url_path):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url_path, view_func=wrapper)
        return wrapper
    return decorator

@trigger_url('/ping')
def ping():
    url = request.args.get('url', 'google.com')  # Default to google.com if no URL is provided
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return result.stdout

if __name__ == '__main__':
    app.run(debug=True)