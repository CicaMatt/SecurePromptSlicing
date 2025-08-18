from functools import wraps
import os
from flask import Flask, send_file, abort

app = Flask(__name__)

def route_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@app.route('/')
def index():
    return "Welcome to the Image Server!"

@route_url('/get_image/<filename>')
def get_image(filename):
    images_folder = 'images'
    file_path = os.path.join(images_folder, filename)
    
    if os.path.isfile(file_path):
        try:
            return send_file(file_path)
        except Exception as e:
            abort(500, description=str(e))
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)