from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            if request.path == url:
                return func(*args, **kwargs)
            else:
                return "This URL does not match the expected path.", 404
        return wrapper
    return decorator

@app.route('/trigger', methods=['GET'])
@route_decorator(url='/trigger')
def check_url():
    return 'URL matched!'

if __name__ == '__main__':
    app.run(debug=True)