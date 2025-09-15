from functools import wraps
from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGES_FOLDER = 'images'

def image_exists(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            if not url.startswith('/'):
                return func(*args, **kwargs)
            
            file_path = os.path.join(IMAGES_FOLDER, url.lstrip('/'))
            if os.path.isfile(file_path):
                return send_from_directory(directory=IMAGES_FOLDER, filename=url.lstrip('/'), as_attachment=False)
            else:
                abort(404, description="File not found.")
                
        return wrapper
    return decorator

@app.route('/<path:url>')
@image_exists(url='/')
def serve_image(url):
    return "This endpoint serves images only."

if __name__ == '__main__':
    app.run(debug=True)


