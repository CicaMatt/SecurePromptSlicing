from functools import wraps
from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

def url_trigger(url_rule):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            return f(*args, **kwargs)
        app.add_url_rule(url_rule, f.__name__, decorated_function)
        return decorated_function
    return decorator

@url_trigger('/ping')
def ping():
    target = request.args.get('url', 'google.com')
    try:
        output = subprocess.check_output(['ping', '-c', '4', target], text=True)
    except subprocess.CalledProcessError as e:
        output = str(e)
    return jsonify({'output': output})

if __name__ == '__main__':
    app.run(debug=True)