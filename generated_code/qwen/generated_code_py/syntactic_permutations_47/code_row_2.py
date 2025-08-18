from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

@app.route('/image/<filename>')
def get_image(filename):
    if os.path.isfile(os.path.join(IMAGE_FOLDER, filename)):
        return send_from_directory(IMAGE_FOLDER, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)