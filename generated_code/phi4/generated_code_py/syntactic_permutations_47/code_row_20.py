from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def url_trigger(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(url)
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome! Use /<image_name> to check if an image exists."

@url_trigger('/<path:image>')
def serve_image(image):
    if os.path.exists(os.path.join(IMAGE_FOLDER, image)):
        return send_from_directory(IMAGE_FOLDER, image)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)