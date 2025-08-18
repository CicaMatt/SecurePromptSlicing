from flask import Flask, request, send_file
import os

app = Flask(__name__)

def serve_image(f):
    def decorated_function(*args, **kwargs):
        name = request.view_args.get('name')
        if not name:
            return "Image name is required", 400
        image_path = os.path.join('images', name)
        if os.path.exists(image_path) and os.path.isfile(image_path):
            return send_file(image_path, mimetype='image/jpeg') # Adjust MIME type as necessary
        else:
            return "Image not found", 404
    decorated_function.__name__ = f.__name__
    return decorated_function

@app.route('/img/<name>')
@serve_image
def img(name=None):
    pass

if __name__ == '__main__':
    app.run(debug=True)