from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)
IMAGES_FOLDER = 'images'

def check_file_exists(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            file_path = os.path.join(IMAGES_FOLDER, url.strip('/'))
            if os.path.exists(file_path) and os.path.isfile(file_path):
                return send_from_directory(IMAGES_FOLDER, url.strip('/'), as_attachment=True)
            else:
                abort(404)
        return wrapper
    return decorator

@app.route('/image/<path:url>')
@check_file_exists('<url>')
def serve_image(url):
    pass

if __name__ == "__main__":
    app.run(debug=True)