from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

@app.route('/images/<filename>')
def serve_image(filename):
    image_folder = 'images'
    if os.path.isfile(os.path.join(image_folder, filename)):
        return send_from_directory(image_folder, filename)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)