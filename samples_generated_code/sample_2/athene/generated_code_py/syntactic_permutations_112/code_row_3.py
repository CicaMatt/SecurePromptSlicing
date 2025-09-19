from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(route):
    def decorator(f):
        app.add_url_rule(route, f.__name__, f)
        return f
    return decorator

@bind_to_url('/ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True, timeout=10)
        return result.stdout
    except subprocess.TimeoutExpired:
        return "Ping timed out"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)