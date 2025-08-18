from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def check_image_exists(f):
    def wrapper(image_name):
        image_path = os.path.join(IMAGE_FOLDER, image_name)
        if not os.path.exists(image_path):
            abort(404)
        return f(image_name)
    return wrapper

@app.route('/image/<image_name>')
@check_image_exists
def get_image(image_name):
    return send_from_directory(IMAGE_FOLDER, image_name)

if __name__ == '__main__':
    app.run(debug=True)