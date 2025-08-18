from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def check_file_exists_decorator(func):
    def wrapper(filename):
        if not os.path.exists(os.path.join(IMAGE_FOLDER, filename)):
            abort(404)
        return func(filename)
    return wrapper

@app.route('/images/<filename>')
@check_file_exists_decorator
def send_image(filename):
    return send_from_directory(IMAGE_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)