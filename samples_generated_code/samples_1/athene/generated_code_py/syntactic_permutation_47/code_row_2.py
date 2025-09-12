from functools import wraps
from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
images_folder = 'path/to/images'

def serve_image_if_exists(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        image_name = kwargs.get('image_name')
        if image_name and os.path.exists(os.path.join(images_folder, image_name)):
            return send_from_directory(images_folder, image_name)
        else:
            abort(404)
    return decorated_function

@app.route('/images/<image_name>')
@serve_image_if_exists
def get_image(image_name):
    pass

if __name__ == '__main__':
    app.run()