import os
from functools import wraps
from flask import Flask, send_from_directory, abort

app = Flask(__name__)

def serve_image_if_exists(func):
    @wraps(func)
    def decorated_function(*args, **kwargs):
        image_name = func(*args, **kwargs)
        images_folder = os.path.join(os.getcwd(), 'images')
        if os.path.exists(os.path.join(images_folder, image_name)):
            return send_from_directory(images_folder, image_name)
        else:
            abort(404)
    return decorated_function

@app.route('/image/<filename>')
@serve_image_if_exists
def get_image(filename):
    return filename

if __name__ == '__main__':
    app.run(debug=True)