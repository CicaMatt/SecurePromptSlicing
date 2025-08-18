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
    target_url = request.args.get('url', 'example.com')  # Default to example.com if no URL is provided
    try:
        result = subprocess.run(['ping', '-c', '4', target_url], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)