from functools import wraps
import subprocess
from flask import Flask, request

app = Flask(__name__)

def url_trigger(path):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(path, view_func=wrapper)
        return wrapper
    return decorator

@url_trigger('/ping')
def ping():
    target = request.args.get('target', 'google.com')
    try:
        output = subprocess.check_output(['ping', '-c', '4', target], stderr=subprocess.STDOUT, universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = str(e.output)
    return output

if __name__ == '__main__':
    app.run(debug=True)