import os
from flask import Flask, send_file, abort

app = Flask(__name__)
IMAGES_FOLDER = 'images'

def check_image_exists(func):
    def wrapper(filename, *args, **kwargs):
        filepath = os.path.join(IMAGES_FOLDER, filename)
        if os.path.isfile(filepath):
            return func(filepath, *args, **kwargs)
        else:
            abort(404, description="Image not found")
    return wrapper

@app.route('/images/<filename>')
@check_image_exists
def serve_image(filepath):
    return send_file(filepath)

if __name__ == '__main__':
    app.run(debug=True)