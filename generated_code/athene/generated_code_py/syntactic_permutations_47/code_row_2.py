from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def serve_image(func):
    def wrapper(filename):
        image_folder = os.path.join(app.root_path, 'images')
        if os.path.exists(os.path.join(image_folder, filename)):
            return func(filename)
        else:
            return "File not found", 404
    return wrapper

@app.route('/images/<path:filename>')
@serve_image
def get_image(filename):
    return send_from_directory(os.path.join(app.root_path, 'images'), filename)

if __name__ == '__main__':
    app.run()