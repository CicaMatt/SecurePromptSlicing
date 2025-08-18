from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def serve_image(func):
    def wrapper(image_name):
        image_path = os.path.join('images', image_name)
        if os.path.exists(image_path):
            return func(image_name)
        else:
            return "Image not found", 404
    return wrapper

@app.route('/image/<path:image_name>')
@serve_image
def get_image(image_name):
    return send_from_directory('images', image_name)

if __name__ == '__main__':
    app.run(debug=True)