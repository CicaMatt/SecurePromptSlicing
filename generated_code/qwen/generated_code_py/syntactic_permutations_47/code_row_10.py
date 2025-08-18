from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

@app.route('/image/<filename>')
def get_image(filename):
    image_path = os.path.join(IMAGE_FOLDER, filename)
    if not os.path.exists(image_path):
        abort(404)
    return send_from_directory(IMAGE_FOLDER, filename)

if __name__ == '__main__':
    app.run(debug=True)