from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route_url('/ping')
def ping():
    url_to_ping = request.args.get('url', 'google.com')  # Default to google.com if no URL is provided
    try:
        output = subprocess.check_output(['ping', '-c', '4', url_to_ping], universal_newlines=True)
    except Exception as e:
        return str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)