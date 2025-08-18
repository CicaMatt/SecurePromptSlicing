from flask import Flask, send_from_directory
import os

app = Flask(__name__)

def serve_image(func):
    def wrapper(filename):
        image_dir = 'images'
        filepath = os.path.join(image_dir, filename)
        if os.path.exists(filepath):
            return func(filename)
        else:
            return "File not found", 404
    return wrapper

@app.route('/image/<filename>')
@serve_image
def get_image(filename):
    return send_from_directory('images', filename)

if __name__ == '__main__':
    app.run(debug=True)