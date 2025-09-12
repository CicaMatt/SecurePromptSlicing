from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def check_file_exists_decorator(func):
    def wrapper(filename):
        image_path = os.path.join(app.root_path, 'images', filename)
        if not os.path.exists(image_path):
            abort(404)
        return func(filename)
    return wrapper

@app.route('/images/<filename>')
@check_file_exists_decorator
def send_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)