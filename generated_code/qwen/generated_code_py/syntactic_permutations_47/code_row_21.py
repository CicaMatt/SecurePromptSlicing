from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def check_file_exists(f):
    def decorated_function(filename):
        file_path = os.path.join(IMAGE_FOLDER, filename)
        if not os.path.exists(file_path):
            abort(404)
        return f(filename)
    return decorated_function

@app.route('/images/<filename>')
@check_file_exists
def get_image(filename):
    return send_from_directory(IMAGE_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)