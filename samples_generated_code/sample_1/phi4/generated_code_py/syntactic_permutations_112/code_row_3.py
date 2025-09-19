from flask import Flask, request
import subprocess

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', view_func=func)
        return func
    return decorator

@app.route('/')
def home():
    return "Ping a URL by appending /ping to the base URL"

@bind_to_url('ping')
def ping():
    url = request.args.get('url', '')
    if not url:
        return "No URL provided", 400
    
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)