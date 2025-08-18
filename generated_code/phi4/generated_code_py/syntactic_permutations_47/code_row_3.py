from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def image_route(url):
    def decorator(func):
        app.route(url)(func)
        return func
    return decorator

@image_route('/get_image/<filename>')
def get_image(filename):
    file_path = os.path.join(IMAGE_FOLDER, filename)
    if os.path.exists(file_path):
        return send_from_directory(IMAGE_FOLDER, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)