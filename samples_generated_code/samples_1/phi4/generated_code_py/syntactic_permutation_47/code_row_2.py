from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def check_image_exists(f):
    def wrapper(url):
        filepath = os.path.join(IMAGE_FOLDER, url)
        if os.path.exists(filepath):
            return f(filepath)
        else:
            abort(404, description="Image not found")
    return wrapper

@app.route('/image/<path:url>')
@check_image_exists
def serve_image(filepath):
    return send_from_directory(directory=IMAGE_FOLDER, filename=os.path.basename(filepath))

if __name__ == '__main__':
    app.run(debug=True)