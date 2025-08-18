from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def serve_image(filename):
    def decorator(func):
        def wrapper(*args, **kwargs):
            image_path = os.path.join(IMAGE_FOLDER, filename)
            if os.path.exists(image_path) and os.path.isfile(image_path):
                return send_from_directory(IMAGE_FOLDER, filename)
            else:
                abort(404)
        wrapper.__name__ = func.__name__
        return wrapper
    return decorator

@app.route('/<filename>')
@serve_image('<filename>')
def serve_file(filename):
    pass

if __name__ == '__main__':
    app.run(debug=True)