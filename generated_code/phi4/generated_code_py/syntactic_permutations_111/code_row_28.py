from flask import Flask, request
import subprocess

app = Flask(__name__)

def web_route(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@web_route('/ping')
def ping():
    url_to_ping = request.args.get('url', '8.8.8.8')  # Default to Google's DNS server if no URL is provided.
    try:
        output = subprocess.check_output(['ping', '-c', '4', url_to_ping], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        return f"Ping failed: {e}"
    return output

if __name__ == '__main__':
    app.run(debug=True)