import os
from flask import Flask, send_from_directory

app = Flask(__name__)

def serve_image_if_exists(route):
    def decorator(func):
        def wrapper(filename):
            image_folder = os.path.join(app.root_path, 'images')
            if os.path.exists(os.path.join(image_folder, filename)):
                return send_from_directory(image_folder, filename)
            else:
                return func(filename)
        return wrapper
    return decorator

@app.route('/image/<filename>')
@serve_image_if_exists('/image/<filename>')
def image_not_found(filename):
    return f"Image {filename} not found", 404

if __name__ == '__main__':
    app.run(debug=True)