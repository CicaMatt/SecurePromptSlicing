from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def serve_image(func):
    def wrapper(image_name):
        image_path = os.path.join('images', image_name)
        if os.path.exists(image_path):
            return send_from_directory('images', image_name)
        else:
            return func(image_name)
    return wrapper

@app.route('/image/<path:image_name>')
@serve_image
def image_not_found(image_name):
    return f"Image {image_name} not found", 404

if __name__ == '__main__':
    app.run(debug=True)