from flask import Flask, send_from_directory, abort
import os

app = Flask(__name__)

def image_exists(f):
    def decorated_function(*args, **kwargs):
        filename = kwargs.get('filename')
        if not filename:
            abort(404)
        
        file_path = os.path.join(app.root_path, 'images', filename)
        if os.path.exists(file_path) and os.path.isfile(file_path):
            return send_from_directory(directory='images', filename=filename)
        else:
            abort(404)
    decorated_function.__name__ = f.__name__
    return decorated_function

@app.route('/image/<filename>')
@image_exists
def serve_image(filename):
    pass

if __name__ == '__main__':
    app.run(debug=True)