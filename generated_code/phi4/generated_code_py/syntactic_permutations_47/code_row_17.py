import os
from functools import wraps
from flask import Flask, request, jsonify

app = Flask(__name__)
IMAGES_FOLDER = 'images'

def route_trigger(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@route_trigger('/check_image/<filename>')
def check_image(filename):
    file_path = os.path.join(IMAGES_FOLDER, filename)
    if os.path.exists(file_path) and os.path.isfile(file_path):
        return jsonify({'exists': True})
    else:
        return jsonify({'exists': False})

if __name__ == '__main__':
    app.run(debug=True)