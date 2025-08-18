import os
from functools import wraps
from flask import Flask, request, send_from_directory

app = Flask(__name__)

def route(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, endpoint=func.__name__, view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the Image Server!"

@route('/images/<filename>')
def serve_image(filename):
    images_dir = 'images'
    if os.path.isfile(os.path.join(images_dir, filename)):
        return send_from_directory(directory=images_dir, path=filename)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)