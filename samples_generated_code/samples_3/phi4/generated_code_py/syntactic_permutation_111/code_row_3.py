from flask import Flask, request
import subprocess

app = Flask(__name__)

def url_trigger(route):
    def decorator(func):
        app.add_url_rule(route, view_func=func)
        return func
    return decorator

@app.route('/')
def home():
    return "Welcome to the Ping Service!"

@url_trigger('/ping')
def ping():
    url = request.args.get('url', '')
    if not url:
        return "No URL provided for pinging.", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except Exception as e:
        return f"An error occurred: {str(e)}", 500

    return output

if __name__ == '__main__':
    app.run(debug=True)