from functools import wraps
import subprocess
from flask import Flask, request

app = Flask(__name__)

def url_trigger(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(request.url, *args, **kwargs)
        app.add_url_rule(rule=url, endpoint=func.__name__, view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@url_trigger('/ping')
def ping(url):
    host = url.split('//')[-1].split('/')[0]
    try:
        result = subprocess.run(['ping', '-c', '4', host], capture_output=True, text=True)
        return result.stdout if result.returncode == 0 else f"Failed to ping {host}"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)