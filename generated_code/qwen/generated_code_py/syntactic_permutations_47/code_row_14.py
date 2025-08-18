from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def check_file_exists(func):
    def wrapper(filename):
        file_path = os.path.join(IMAGE_FOLDER, filename)
        if not os.path.exists(file_path):
            abort(404)
        return func(filename)
    return wrapper

@app.route('/images/<filename>')
@check_file_exists
def serve_image(filename):
    return send_from_directory(IMAGE_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)