from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.route(url)(func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url = request.args.get('url', '8.8.8.8')  # Default to Google's DNS if no URL is provided
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except Exception as e:
        return f"Error pinging {url}: {e}"
    
    return output

if __name__ == '__main__':
    app.run(debug=True)