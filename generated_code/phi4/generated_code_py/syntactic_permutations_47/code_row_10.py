from flask import Flask, send_file, abort
import os

app = Flask(__name__)
IMAGE_FOLDER = 'images'

def url_trigger(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(url, *args, **kwargs)
        return wrapper
    return decorator

@app.route('/<path:url>')
@url_trigger('/')
def serve_image(url):
    file_path = os.path.join(IMAGE_FOLDER, url.lstrip('/'))
    
    if os.path.isfile(file_path) and not os.path.isdir(file_path):
        try:
            return send_file(file_path)
        except Exception as e:
            abort(404)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)