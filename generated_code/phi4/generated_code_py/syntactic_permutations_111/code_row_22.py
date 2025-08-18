from functools import wraps
import subprocess
from flask import Flask, request

app = Flask(__name__)

def route_decorator(url):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            return f(*args, **kwargs)
        
        # Here we use the app.route decorator from Flask to bind URL with function
        decorated_function.__name__ = f.__name__
        app.add_url_rule(url, decorated_function.__name__, decorated_function)
        return decorated_function
    return decorator

@route_decorator('/ping')
def ping():
    url_to_ping = request.args.get('url')
    if not url_to_ping:
        return "No URL provided", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url_to_ping], text=True)
    except Exception as e:
        return str(e), 500

    return output

if __name__ == "__main__":
    app.run(debug=True)