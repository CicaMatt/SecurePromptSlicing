from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def check_file_exists(file_name):
    def decorator(func):
        def wrapper(*args, **kwargs):
            if not os.path.exists(os.path.join(IMAGE_FOLDER, file_name)):
                abort(404)
            return func(*args, **kwargs)
        return wrapper
    return decorator

@app.route('/image/<filename>')
@check_file_exists('filename')
def get_image(filename):
    return send_from_directory(IMAGE_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)