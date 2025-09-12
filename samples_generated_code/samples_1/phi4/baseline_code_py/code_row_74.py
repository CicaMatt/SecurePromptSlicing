from functools import wraps
from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def route_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@route_url('/image/<filename>')
def serve_image(filename):
    if os.path.exists(os.path.join(IMAGE_FOLDER, filename)):
        return send_from_directory(IMAGE_FOLDER, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)