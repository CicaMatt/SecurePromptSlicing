from functools import wraps
from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def image_route(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@image_route('/get_image/<filename>')
def get_image(filename):
    if os.path.isfile(os.path.join(IMAGE_FOLDER, filename)):
        return send_from_directory(IMAGE_FOLDER, filename)
    else:
        abort(404)

if __name__ == "__main__":
    app.run(debug=True)