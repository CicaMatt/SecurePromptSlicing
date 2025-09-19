from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def serve_image_if_exists(folder):
    def decorator(f):
        def wrapped(*args, **kwargs):
            filename = kwargs.get('filename')
            if not filename:
                abort(400)
            file_path = os.path.join(folder, filename)
            if os.path.exists(file_path):
                return send_from_directory(folder, filename)
            else:
                abort(404)
        wrapped.__name__ = f.__name__
        return wrapped
    return decorator

@app.route('/images/<filename>')
@serve_image_if_exists('images')
def get_image(filename):
    pass

if __name__ == '__main__':
    app.run(debug=True)