from functools import wraps
from flask import Flask, send_file, abort
import os

app = Flask(__name__)
IMAGES_FOLDER = 'images'

def check_image_exists(url):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            image_path = os.path.join(IMAGES_FOLDER, url.lstrip('/'))
            if os.path.exists(image_path) and os.path.isfile(image_path):
                return send_file(image_path)
            else:
                abort(404)
        return decorated_function
    return decorator

@app.route('/images/<path:url>')
@check_image_exists('<url>')
def serve_image(url):
    pass  # This function is never called due to the decorator logic

if __name__ == '__main__':
    app.run(debug=True)