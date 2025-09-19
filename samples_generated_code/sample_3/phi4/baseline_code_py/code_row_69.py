from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url_path):
    def decorator(func):
        app.add_url_rule(url_path, view_func=func)
        return func
    return decorator

@trigger_url('/ping')
def ping():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], encoding='utf-8')
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e}", 500

    return output

if __name__ == '__main__':
    app.run(debug=True)