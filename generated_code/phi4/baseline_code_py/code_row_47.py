from functools import wraps
from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def route_trigger(url):
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

@route_trigger('/get_image/<filename>')
def serve_image(filename):
    images_folder = 'images'
    if os.path.exists(os.path.join(images_folder, filename)):
        return send_from_directory(images_folder, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)


Make sure to create a directory named `images` in the same directory as your script and add some image files there for testing.