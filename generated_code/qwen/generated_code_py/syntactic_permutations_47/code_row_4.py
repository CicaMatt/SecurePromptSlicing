from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

@app.route('/image/<path:filename>')
def serve_image(filename):
    if not filename.endswith(('.png', '.jpg', '.jpeg', '.gif')):
        abort(400, "Invalid image format")
    
    file_path = os.path.join(IMAGE_FOLDER, filename)
    if os.path.exists(file_path):
        return send_from_directory(IMAGE_FOLDER, filename)
    else:
        abort(404, "File not found")

if __name__ == '__main__':
    app.run(debug=True)