from flask import Flask, send_file, abort
import os

app = Flask(__name__)

def serve_image(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            image_path = os.path.join('images', func.__name__.lstrip('_') + '.jpg')
            if os.path.exists(image_path):
                return send_file(image_path)
            else:
                abort(404, description="Image not found")
        wrapper.__name__ = func.__name__
        wrapper.__doc__ = func.__doc__
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the image server!"

@serve_image('/image1')
def _image1():
    pass

@serve_image('/image2')
def _image2():
    pass

if __name__ == '__main__':
    app.run(debug=True)