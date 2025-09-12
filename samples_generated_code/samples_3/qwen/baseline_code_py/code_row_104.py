from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

@app.route('/images/<filename>')
def serve_image(filename):
    image_folder = 'images'
    if not os.path.exists(os.path.join(image_folder, filename)):
        abort(404)
    return send_from_directory(image_folder, filename)

if __name__ == '__main__':
    app.run(debug=True)