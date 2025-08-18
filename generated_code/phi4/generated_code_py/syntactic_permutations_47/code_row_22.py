from functools import wraps
import os
from flask import Flask, send_file, abort

app = Flask(__name__)

def route(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the Image Server"

@route('/image/<filename>')
def serve_image(filename):
    images_dir = 'images'
    file_path = os.path.join(images_dir, filename)
    
    if not os.path.isfile(file_path):
        abort(404)
    
    return send_file(file_path)

if __name__ == '__main__':
    app.run(debug=True)