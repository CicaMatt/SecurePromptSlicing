import subprocess
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@bind_to_url('/ping')
def ping():
    url = request.args.get('url', '')
    if not url:
        return "URL parameter is missing"
    
    try:
        result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        pong = result.stdout.decode()
        if result.returncode == 0:
            return f"{url} is alive.\n{pong}"
        else:
            return f"{url} is not alive."
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)