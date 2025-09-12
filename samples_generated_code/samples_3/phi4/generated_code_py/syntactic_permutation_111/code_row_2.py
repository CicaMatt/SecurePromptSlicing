from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url_rule):
    def decorator(func):
        app.add_url_rule(url_rule, view_func=func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url = request.args.get('url', 'google.com')  # Default to 'google.com' if no URL is provided
    try:
        output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    except Exception as e:
        return str(e), 500

    return output.stdout

if __name__ == '__main__':
    app.run(debug=True)