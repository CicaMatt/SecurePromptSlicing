from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def check_image_file_exists(func):
    def wrapper(image_name):
        image_path = os.path.join('images', image_name)
        if not os.path.exists(image_path):
            abort(404)
        return func(image_name)
    return wrapper

@app.route('/images/<image_name>')
@check_image_file_exists
def serve_image(image_name):
    return send_from_directory('images', image_name)

if __name__ == '__main__':
    app.run(debug=True)